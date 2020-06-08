/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:55:14 by selly             #+#    #+#             */
/*   Updated: 2019/09/29 13:04:59 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	size_t			i;
	unsigned char	*point;

	i = 0;
	point = (unsigned char *)str;
	while (i < len)
	{
		point[i] = (unsigned char)c;
		i++;
	}
	return ((void *)str);
}
