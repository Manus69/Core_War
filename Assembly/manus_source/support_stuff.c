#include "function_prototypes.h"
#include <limits.h>

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

int is_in_string(const char *string, char c)
{
    int n;
    int last_occurence;

    last_occurence = -1;
    n = 0;
    while (string[n] != '\0')
    {
        if (string[n] == c)
            last_occurence = n;
        n = n + 1;
    }
    return (last_occurence);
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

unsigned int binary_to_unsigned_decimal(char *binary_number)
{
    unsigned int result;
    unsigned int current_base;
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

char *ft_itoa_base_local(unsigned int n, unsigned int base)
{
    unsigned long max_power;
    unsigned int m;
    char *result;
    static const char *char_set = "0123456789abcdef";
    unsigned int index;

    max_power = 1;
    m = 0;
    while (max_power <= n)
    {
        max_power = max_power * base;
        m = m + 1;
    }
    max_power = max_power / base;
    result = ft_strnew(sizeof(char) * m);
    index = 0;
    while (max_power > 0)
    {
        result[index] = char_set[n / max_power];
        n = n % max_power;
        max_power = max_power / base;
        index = index + 1;
    }
    return (result);
}

char *get_hex_with_padding(int decimal, int number_of_bytes)
{
    int m;
    int initial_length;
    char *resulting_string;
    int resulting_string_length;
    char *hex_number;
    
    // hex_number = ft_itoa_base(decimal, 16);
    hex_number = ft_itoa_base_local(decimal, NUMBER_SYSTEM_BASE);
    initial_length = ft_strlen(hex_number);
    resulting_string_length = number_of_bytes * 2;
    if (resulting_string_length < initial_length)
        resulting_string_length = initial_length;
    resulting_string = ft_strnew(resulting_string_length);
    m = 0;
    while (m < resulting_string_length)
    {
        resulting_string[m] = '0';
        m = m + 1;
    }
    m = 0;
    while (m < initial_length)
    {
        resulting_string[resulting_string_length - 1 - m] = hex_number[initial_length - 1 - m];
        m = m + 1;
    }
    free(hex_number);
    return (resulting_string);
}

// char *decimal_to_hex(int n, int number_of_bytes)
// {
//     int decimal;
//     char *binary_complement;
//     char *number_string;

//     if (n >= 0)
//     {
//         return (get_hex_with_padding(n, number_of_bytes));
//     }
//     n = -n;
//     number_string = ft_itoa_base(n, 2);
//     binary_complement = get_binary_complement(number_string, number_of_bytes); //leak;
//     decimal = binary_to_decimal(binary_complement);
//     return (get_hex_with_padding(decimal, number_of_bytes));
// }

char *decimal_to_hex_mk2(int n, int number_of_bytes) //using unsigned int; does it work correctly?
{
    unsigned int decimal;
    char *binary_complement;
    char *number_string;

    if (n >= 0)
    {
        return (get_hex_with_padding(n, number_of_bytes));
    }
    n = -n;
    number_string = ft_itoa_base(n, 2);
    binary_complement = get_binary_complement(number_string, number_of_bytes); //leak;
    decimal = binary_to_unsigned_decimal(binary_complement);
    return (get_hex_with_padding(decimal, number_of_bytes));
}

long why_atol(const char *number_string) //hope i didnt make a blunder;
{
    long result;
    unsigned int n;
    int sign;

    result = 0;
    sign = (number_string[0] == '-') ? -1 : 1;
    n = 0;
    while (number_string[n] != '\0')
    {
        if (n == 0 && number_string[n] == '-')
        {
            n = n + 1;
            continue ;
        }
        if (!is_a_member(DIGITS, number_string[n]))
            return (sign * result);
        result = (result * 10) + ((int)number_string[n] - '0');
        n = n + 1;
    }
    return (sign * result);
}

int check_number_string(const char *number_string)
{
    long number;
    unsigned int length;

    length = ft_strlen(number_string);
    if (length > 12) //longer than INT_MIN
        return (0);
    number = why_atol(number_string);
    if (number < INT_MIN || number > INT_MAX)
        return (0);
    return (1);
}