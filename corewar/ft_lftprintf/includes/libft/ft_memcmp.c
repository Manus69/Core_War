/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 13:10:58 by selly             #+#    #+#             */
/*   Updated: 2019/05/06 15:12:14 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(void const *s1, void const *s2, size_t n)
{
	unsigned char			*s1_p;
	unsigned const char		*s2_p;
	int						result;

	s1_p = (unsigned char *)s1;
	s2_p = (unsigned const char *)s2;
	while (n)
	{
		if ((result = *s1_p - *s2_p) != 0)
			return (result);
		s1_p++;
		s2_p++;
		n--;
	}
	return (0);
}
