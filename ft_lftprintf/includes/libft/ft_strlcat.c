/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 14:43:18 by selly             #+#    #+#             */
/*   Updated: 2019/05/06 14:45:02 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, char const *src, size_t n)
{
	size_t		i;
	size_t		a;
	size_t		dest_size;

	i = 0;
	a = 0;
	dest_size = ft_strlen(dest);
	if (n > 0 && n > dest_size)
	{
		i = dest_size;
		while (src[a] && i < n - 1)
			dest[i++] = src[a++];
		dest[i] = '\0';
		return (ft_strlen(src) + dest_size);
	}
	return (ft_strlen(src) + n);
}
