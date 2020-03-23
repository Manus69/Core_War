/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_thebigest_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:18:10 by selly             #+#    #+#             */
/*   Updated: 2019/05/04 15:45:57 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_thebigest_word(char const *str, char c)
{
	int		max;
	int		word;

	max = 0;
	word = 0;
	if (!str)
		return (0);
	while (*str == c)
		str++;
	while (*str)
	{
		if (*str != c)
			word++;
		if (*str == c && *(str + 1) != c && *(str + 1) != '\0')
		{
			if (max < word)
				max = word;
			word = 0;
		}
		str++;
	}
	return (max);
}
