/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:09:07 by selly             #+#    #+#             */
/*   Updated: 2019/05/06 16:34:59 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *s, int c)
{
	char const		*point;

	point = s;
	if (c == '\0')
	{
		while (*point)
			point++;
		return ((char *)point);
	}
	if (!s || !c)
		return (0);
	while (*point)
		point++;
	while (point > s)
	{
		point--;
		if (((unsigned char)*point) == c)
			return ((char *)point);
	}
	return (0);
}
