/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_dizasm_init.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:36:52 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:46:55 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		fill_null_point(t_dsm *src_code)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		if (src_code->input[src_code->current_position++])
			return (FAIL);
	}
	return (SUCCESS);
}

int		fill_name(t_dsm *src_code)
{
	if ((src_code->current_position + PROG_NAME_LENGTH) > src_code->file_len)
		return (FAIL);
	ft_bzero(src_code->fill_file.name, PROG_NAME_LENGTH + 1);
	ft_memcpy(&src_code->fill_file.name[0],\
			&src_code->input[src_code->current_position], PROG_NAME_LENGTH);
	src_code->current_position += PROG_NAME_LENGTH;
	if (!fill_null_point(src_code))
		return (FAIL);
	return (SUCCESS);
}

int		fill_code_size(t_dsm *src_code)
{
	unsigned int	*value;
	int				i;
	int				val;

	if ((src_code->current_position + 4) > src_code->file_len)
		return (FAIL);
	src_code->fill_file.champ_size = 0;
	if (!(value = (unsigned int *)malloc(4)))
		return (FAIL);
	i = -1;
	val = 3;
	while (++i < 4)
	{
		((unsigned char*)value)[val] =\
					src_code->input[src_code->current_position];
		src_code->current_position++;
		val--;
	}
	src_code->fill_file.champ_size = *value;
	free(value);
	if (src_code->fill_file.champ_size > CHAMP_MAX_SIZE)
		return (FAIL);
	return (SUCCESS);
}

int		fill_comment(t_dsm *src_code)
{
	if ((src_code->current_position + COMMENT_LENGTH) > src_code->file_len)
		return (FAIL);
	ft_bzero(src_code->fill_file.comment, COMMENT_LENGTH + 1);
	ft_memcpy(&src_code->fill_file.comment[0],\
			&src_code->input[src_code->current_position], COMMENT_LENGTH);
	src_code->current_position += COMMENT_LENGTH;
	if (!fill_null_point(src_code))
		return (FAIL);
	return (SUCCESS);
}

int		fill_diff_code_size(t_dsm *src_code)
{
	if ((src_code->current_position + src_code->fill_file.champ_size) >\
			src_code->file_len)
		return (FAIL);
	return (SUCCESS);
}
