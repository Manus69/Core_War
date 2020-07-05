/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 14:49:54 by selly             #+#    #+#             */
/*   Updated: 2019/05/10 13:23:12 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		i;
	int		a;

	i = 0;
	a = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(new = ft_strnew((ft_strlen(s1) + ft_strlen(s2)))))
		return (NULL);
	while (s1[i] != '\0')
	{
		new[a] = s1[i];
		a++;
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		new[a] = s2[i];
		a++;
		i++;
	}
	return (new);
}
