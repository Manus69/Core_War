/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 20:22:31 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/26 20:23:30 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		generic_token_string_check(char *string,
						char character, int start)
{
	int length;

	length = ft_strlen(string);
	if (length < 2)
		return (0);
	if (start && (string[0] != character))
		return (0);
	if (!start && (string[length - 1] != character))
		return (0);
	return (1);
}

int		check_substring_characters(char *string,
			int start_index, int end_index, char *set)
{
	int n;

	if (end_index < start_index)
		return (0);
	n = start_index;
	while (n <= end_index)
	{
		if (!is_a_member(set, string[n]))
			return (0);
		n = n + 1;
	}
	return (1);
}

int		check_symbol(char *string, char symbol)
{
	if (ft_strlen(string) == 1 && string[0] == symbol)
		return (1);
	return (0);
}
