/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_file.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:29:28 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:12:41 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		take_start(char *old_name)
{
	int start;
	int i;

	i = -1;
	start = 0;
	while (old_name[++i])
	{
		if (old_name[i] == '/')
			start = i + 1;
	}
	return (start);
}

int		take_new_name(t_dsm *src_code, char *old_name)
{
	int i;
	int start_name;

	start_name = take_start(old_name);
	if (!((src_code->file_name) =\
				(char *)malloc((ft_strlen(old_name) - start_name) + 1)))
		return (FAIL);
	i = 0;
	while (old_name[start_name] && old_name[start_name] != '.')
	{
		(src_code->file_name)[i] = old_name[start_name];
		i++;
		start_name++;
	}
	(src_code->file_name)[i++] = '.';
	(src_code->file_name)[i++] = 's';
	(src_code->file_name)[i++] = '\0';
	return (SUCCESS);
}

int		fill_new_file(t_dsm *src_code, t_flag *has_flag)
{
	int		fd;
	char	*file_name;

	if (has_flag->change_name)
		file_name = has_flag->new_file_name;
	else
		file_name = src_code->file_name;
	if ((fd = open(file_name,\
					O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 1)
	{
		free(src_code->file_name);
		return (FAIL);
	}
	ft_printf("Writing output program to %s\n", file_name);
	ft_putstr_fd(src_code->output, fd);
	close(fd);
	free(src_code->file_name);
	src_code->file_name = NULL;
	return (SUCCESS);
}
