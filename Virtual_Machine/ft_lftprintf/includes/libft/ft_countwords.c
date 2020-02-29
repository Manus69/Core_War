/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:12:10 by selly             #+#    #+#             */
/*   Updated: 2019/05/04 15:40:00 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countwords(char const *str, char c)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	while (*str == c)
		str++;
	if (*str != c)
		i++;
	while (*str)
	{
		if (*str == c && *(str + 1) != c && *(str + 1) != '\0')
			i++;
		str++;
	}
	return (i);
}
