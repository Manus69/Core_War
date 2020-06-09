#include "function_prototypes.h"
#include "constants.h"
// #include <limits.h>

int				binary_to_decimal(char *binary_number)
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

unsigned int	binary_to_unsigned_decimal(char *binary_number)
{
	unsigned int	result;
	unsigned int	current_base;
	int				number_of_bits;
	int				n;

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

char		*get_hex_with_padding(int decimal, int number_of_bytes)
{
	int		m;
	int		initial_length;
	char	*resulting_string;
	int		resulting_string_length;
	char	*hex_number;
	
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

char		*decimal_to_hex_mk2(int n, int number_of_bytes)
{
	unsigned int	decimal;
	char			*binary_complement;
	char			*number_string;
	char			*hex_with_padding;

	if (n >= 0)
	{
		return (get_hex_with_padding(n, number_of_bytes));
	}
	n = -n;
	number_string = ft_itoa_base(n, 2);
	binary_complement = get_binary_complement(number_string, number_of_bytes);
	decimal = binary_to_unsigned_decimal(binary_complement);
	hex_with_padding = get_hex_with_padding(decimal, number_of_bytes);
	free(binary_complement);
	free(number_string);
	return (hex_with_padding);
}
