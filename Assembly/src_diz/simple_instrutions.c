/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_instrutions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:36:20 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:36:46 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		write_dir_without_arg_type(t_dsm *src_code, int size_t_dir)
{
	char	*number;
	int		i;

	if (size_t_dir == 2)
	{
		if (!(number = take_short_dir(src_code)))
			return (FAIL);
	}
	else
	{
		if (!(number = take_simple_dir(src_code)))
			return (FAIL);
	}
	i = -1;
	src_code->output[src_code->output_position++] = DIRECT_CHAR;
	while (number[++i])
	{
		src_code->output[src_code->output_position] = number[i];
		src_code->output_position++;
	}
	free(number);
	return (SUCCESS);
}

int		fill_simple_instruction(t_dsm *src_code)
{
	int op_code;
	int size_t_dir;

	op_code = src_code->input[src_code->current_position];
	src_code->current_position += 1;
	size_t_dir = 2;
	if (op_code == 1)
		size_t_dir = 4;
	if (src_code->current_position >= src_code->file_len)
		return (FAIL);
	write_instruction(src_code, op_code);
	write_dir_without_arg_type(src_code, size_t_dir);
	src_code->output[src_code->output_position++] = '\n';
	return (SUCCESS);
}
