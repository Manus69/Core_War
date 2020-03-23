/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:12:34 by selly             #+#    #+#             */
/*   Updated: 2019/05/06 17:30:00 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char const *haystack, char const *needle)
{
	char const *p_haystack;
	char const *find;

	if (!*needle)
		return ((char *)haystack);
	while (*haystack)
	{
		p_haystack = haystack;
		find = needle;
		while (*p_haystack && *find)
		{
			if (*p_haystack++ != *find)
				break ;
			else
				find++;
		}
		if (*find == '\0' || *find == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
