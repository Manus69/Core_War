/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:00:44 by selly             #+#    #+#             */
/*   Updated: 2019/10/21 16:08:50 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_mod(int num, unsigned int len, int c)
{
	char	*str;

	len = ft_length(num, 2);
	c = num;
	if (num < 0)
		c = -c;
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	str[len--] = '\0';
	while (c)
	{
		str[len--] = c % 10 + '0';
		c /= 10;
	}
	if (num < 0)
		str[0] = '-';
	return (str);
}
