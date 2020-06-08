/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_octo_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:32:18 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:33:10 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		err_validate(t_dsm *src_code)
{
	free(src_code->input);
	ft_putstr_fd("ERROR : *.cor ARE BAD\n", 2);
	return (FAIL);
}

int		err_output(t_dsm *src_code)
{
	free(src_code->input);
	if (src_code->output)
		free(src_code->output);
	ft_putstr_fd("ERROR : CAN'T WRITE OUTPUT\n", 2);
	return (FAIL);
}

int		taste_magic(unsigned char *input)
{
	int *value;
	int i;
	int val;

	if (!(value = (int *)malloc(sizeof(int))))
		return (FAIL);
	i = -1;
	val = 3;
	*value = COREWAR_EXEC_MAGIC;
	while (++i < 4)
	{
		if (input[i] != ((unsigned char*)value)[val])
		{
			free(value);
			return (FAIL);
		}
		val--;
	}
	free(value);
	return (SUCCESS);
}

int		validate_binary(t_dsm *src_code)
{
	if (src_code->file_len < 4 || !taste_magic(src_code->input))
		return (err_validate(src_code));
	src_code->current_position = 4;
	if (!fill_name(src_code))
		return (err_validate(src_code));
	if (!fill_code_size(src_code))
		return (err_validate(src_code));
	if (!fill_comment(src_code))
		return (err_validate(src_code));
	if (!fill_diff_code_size(src_code))
		return (err_validate(src_code));
	if (!(collect_pre_print(src_code)))
		return (err_output(src_code));
	if (!(walk_throw(src_code)))
		return (err_output(src_code));
	if (!(fill_new_file(src_code)))
		return (err_output(src_code));
	free(src_code->input);
	free(src_code->output);
	return (SUCCESS);
}

int		read_my_binary(char *str, unsigned char **buf)
{
	int		fd;
	size_t	file_len;

	file_len = 0;
	if ((fd = open(str, O_RDONLY)) < 0)
		return (err_out("ERROR : FILE DOES NOT EXIST"));
	(*buf) = ft_binary_read(fd, &file_len);
	close(fd);
	if (!(*buf) || file_len == 0)
		return (err_out("ERROR : CAN'T READ"));
	return (file_len);
}
