/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:41:56 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/06/27 16:42:06 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

int		is_label(char *string)
{
	unsigned int	n;
	unsigned int	length;

	if (!generic_token_string_check(string, LABEL_CHAR, 0))
		return (0);
	n = 0;
	length = ft_strlen(string);
	while (n < length - 1)
	{
		if (!is_a_member(LABEL_CHARS, string[n]))
			return (0);
		n = n + 1;
	}
	return (1);
}

int		is_registry(char *string)
{
	int				n;

	if (!generic_token_string_check(string, 'r', 1))
		return (0);
	n = 1;
	while (string[n] != '\0')
	{
		if (!is_a_member(DIGITS, string[n]))
			return (0);
		n = n + 1;
	}
	return (1);
}

int		is_direct(char *string)
{
	int				n;
	int				length;

	if (!generic_token_string_check(string, DIRECT_CHAR, 1))
		return (0);
	n = 1;
	length = ft_strlen(string);
	if (string[n] == LABEL_CHAR && (length > 2))
	{
		if (check_substring_characters(string, 2, length - 1, LABEL_CHARS))
			return (1);
	}
	else if (is_a_member(DIGITS, string[n]))
	{
		if (check_substring_characters(string, 1, length - 1, DIGITS))
			return (1);
	}
	else if (string[n] == '-' && length > 2)
	{
		if (check_substring_characters(string, 2, length - 1, DIGITS))
			return (1);
	}
	return (0);
}

int		is_indirect(char *string)
{
	int				n;
	int				length;

	n = 0;
	length = ft_strlen(string);
	if (string[n] == LABEL_CHAR && (length > 1))
	{
		if (check_substring_characters(string, 1, length - 1, LABEL_CHARS))
			return (1);
	}
	else if (is_a_member(DIGITS, string[n]))
	{
		if (check_substring_characters(string, 0, length - 1, DIGITS))
			return (1);
	}
	else if (string[n] == '-' && (length > 1))
	{
		if (check_substring_characters(string, 1, length - 1, DIGITS))
			return (1);
	}
	return (0);
}
