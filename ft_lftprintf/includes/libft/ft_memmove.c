/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:31:18 by selly             #+#    #+#             */
/*   Updated: 2019/05/11 17:01:58 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, void const *src, size_t n)
{
	unsigned char		*dest_p;
	unsigned const char	*src_p;

	dest_p = (unsigned char *)dest;
	src_p = (unsigned const char *)src;
	if (dest_p <= src_p)
	{
		while (n--)
		{
			*dest_p = *src_p;
			dest_p++;
			src_p++;
		}
	}
	else
	{
		dest_p += n;
		src_p += n;
		while (n--)
			*--dest_p = *--src_p;
	}
	return ((void *)dest);
}
