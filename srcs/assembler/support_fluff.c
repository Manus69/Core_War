/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support_fluff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:29:34 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 17:31:19 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	get_char(int file)
{
	char character;

	if (read(file, &character, 1) > 0)
		return (character);
	return (-1);
}

char	skip_to_char(int file, char c)
{
	char current_char;

	while ((current_char = get_char(file)) != -1)
	{
		if (current_char == c)
			return (current_char);
	}
	return (-1);
}

int		is_a_member(const char *set, char c)
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

int		is_in_string(const char *string, char c)
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

char	*concat(char *lhs, char *rhs)
{
	char			*result;
	unsigned int	index;
	unsigned int	n;

	result = ft_strnew(ft_strlen(lhs) + ft_strlen(rhs));
	index = 0;
	n = 0;
	while (lhs[n] != '\0')
	{
		result[n] = lhs[n];
		n = n + 1;
	}
	index = n;
	n = 0;
	while (rhs[n] != '\0')
	{
		result[index + n] = rhs[n];
		n = n + 1;
	}
	return (result);
}
