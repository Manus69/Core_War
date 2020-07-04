/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:04:45 by selly             #+#    #+#             */
/*   Updated: 2019/05/11 17:06:19 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void const *s, int c, size_t n)
{
	unsigned char	*point;

	point = (unsigned char *)s;
	while (n)
	{
		if (*point == (unsigned char)c)
			return ((void *)point);
		point++;
		n--;
	}
	return (NULL);
}
