#include "function_prototypes.h"

int is_a_member(char *set, char c)
{
    int n;

    n = 0;
    while (set[n] != '\0')
    {
        if (set[n] == c)
            return (1);
        n = n + 1;
    }
    return (0);
}

void carry_propagate(char *number, int index, int bytes_left)
{
    if (bytes_left == 0)
        return ;
    if (number[index] == '1')
    {
        number[index] = '0';
        carry_propagate(number, index - 1, bytes_left - 1);
    }
    else if (number[index] == '0')
        number[index] = '1';
}

char *get_binary_complement(char *binary_number, int number_of_bytes)
{
    char *complement;
    int n;
    int initial_number_of_bits;
    int final_number_of_bits;

    final_number_of_bits = number_of_bytes * 8;
    initial_number_of_bits = ft_strlen(binary_number);
    if (final_number_of_bits < initial_number_of_bits)
        return (NULL); //this is questionable;
    complement = ft_strnew(final_number_of_bits);
    n = 0;
    while (n < initial_number_of_bits)
    {
        if (binary_number[initial_number_of_bits - n - 1] == '0')
            complement[final_number_of_bits - 1 - n] = '1';
        else
            complement[final_number_of_bits - 1 - n] = '0';
        n = n + 1;
    }
    while (n < final_number_of_bits)
    {
        complement[final_number_of_bits - 1 - n] = '1';
        n = n + 1;
    }
    carry_propagate(complement, final_number_of_bits - 1, final_number_of_bits);
    return (complement);
}

int binary_to_decimal(char *binary_number)
{
    int result;
    int current_base;
    int number_of_bits;
    int n;

    result = 0;
    current_base = 1;
    n = 0;
    number_of_bits = ft_strlen(binary_number);
    while (n < number_of_bits)
    {
        if (binary_number[number_of_bits - 1 - n] == '1')
            result = result + current_base;
        current_base = current_base * 2;
        n = n + 1;
    }
    return (result);
}

char *int_to_hex(int n, int number_of_bytes)
{
    int decimal;
    char *binary_complement;

    if (n >= 0)
        return (ft_itoa_base(n, 16));
    n = -n;
    binary_complement = get_binary_complement(ft_itoa_base(n, 2), number_of_bytes); //leak;
    decimal = binary_to_decimal(binary_complement);
    return (ft_itoa_base(decimal, 16));
}