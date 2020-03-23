/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cutstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 20:17:03 by selly             #+#    #+#             */
/*   Updated: 2019/09/19 20:20:26 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cutstr(char *str, int i)
{
	char	*new;
	int		a;

	if (!(new = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	a = 0;
	while (i)
	{
		new[a] = str[a];
		a++;
		i--;
	}
	new[a] = '\0';
	return (new);
}
