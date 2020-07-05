/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/04 17:41:55 by selly             #+#    #+#             */
/*   Updated: 2019/05/14 12:37:11 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		is_space(char const c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char			*ft_strtrim(char const *s)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	while (is_space(*s))
		s++;
	new = ft_strdup(s);
	if (!new)
		return (NULL);
	i = ft_strlen(new);
	i--;
	while (i && new[i] && is_space(s[i]))
		i--;
	new = ft_strsub(new, 0, (i + 1));
	if (!new)
		return (NULL);
	return (new);
}
