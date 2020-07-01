/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:50:39 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:51:44 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*replace_extension(const char *file_name, t_container *container)
{
	unsigned int	length;
	char			*replacing_string;

	if (ft_strlen(file_name) < 3)
		invoke_error("File name error;\n", NULL, NULL, container);
	length = ft_strlen(file_name) + 2;
	replacing_string = ft_strnew(length);
	replacing_string = ft_strcpy(replacing_string, file_name);
	replacing_string[length - 3] = 'c';
	replacing_string[length - 2] = 'o';
	replacing_string[length - 1] = 'r';
	return (replacing_string);
}

char	*trim_file_name(const char *file_name, t_container *container)
{
	unsigned int	length;
	char			*resulting_string;
	int				slash_index;

	length = ft_strlen(file_name);
	if (length < 3)
		invoke_error("File name error while trimmig;\n", NULL, NULL, container);
	slash_index = is_in_string(file_name, '/');
	if (slash_index == -1)
		return (ft_strdup(file_name));
	resulting_string =
	ft_strsub(file_name, slash_index + 1, length - slash_index - 1);
	return (resulting_string);
}
