/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_scuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:32:04 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 18:52:44 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

long		why_atol(const char *number_string)
{
	long			result;
	long			previous_result;
	unsigned int	n;
	int				sign;

	result = 0;
	previous_result = 0;
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
		if (result < previous_result)
			return ((sign == -1) ? 0 : -1);
		previous_result = result;
		n = n + 1;
	}
	return (sign * result);
}

char		*ft_itoa_base_local(unsigned int n, unsigned int base)
{
	unsigned long		max_power;
	unsigned int		m;
	char				*result;
	unsigned int		index;
	static const char	*char_set = "0123456789abcdef";

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

void		carry_propagate(char *number, int index, int bytes_left)
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

char		*get_binary_complement(char *binary_number, int number_of_bytes)
{
	char	*complement;
	int		n;
	int		initial_number_of_bits;
	int		final_number_of_bits;

	final_number_of_bits = number_of_bytes * 8;
	initial_number_of_bits = ft_strlen(binary_number);
	if (final_number_of_bits < initial_number_of_bits)
		initial_number_of_bits = final_number_of_bits;
	complement = ft_strnew(final_number_of_bits);
	n = 0;
	while (n < initial_number_of_bits)
	{
		(binary_number[initial_number_of_bits - n - 1] == '0') ?\
			(complement[final_number_of_bits - 1 - n] = '1') :\
			(complement[final_number_of_bits - 1 - n] = '0');
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
