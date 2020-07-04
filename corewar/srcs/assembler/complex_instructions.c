/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:24:07 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:04:34 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				write_ind(t_dsm *src_code, t_argum *args, int j)
{
	char	*number;
	int		i;

	if (!(number = take_short_dir(src_code)))
		return (FAIL);
	i = -1;
	j++;
	while (number[++i])
	{
		src_code->output[src_code->output_position] = number[i];
		src_code->output_position++;
	}
	free(number);
	args++;
	args--;
	return (SUCCESS);
}

int				write_dir(t_dsm *src_code, t_argum *args, int j)
{
	char	*number;
	int		i;

	if (args->arg_size[j] == 2)
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

static void		init_functions_args(int (*actions[])(t_dsm *, t_argum *, int))
{
	actions[0] = NULL;
	actions[1] = &write_reg;
	actions[2] = &write_dir;
	actions[3] = &write_ind;
}

int				write_args(t_dsm *src_code, t_argum *args)
{
	int i;
	int (*actions[4])(t_dsm *, t_argum *, int);

	i = -1;
	init_functions_args(actions);
	while (++i < args->args_count)
	{
		if (!(actions[args->arg_type[i]](src_code, args, i)))
			return (FAIL);
		src_code->output[src_code->output_position++] = SEPARATOR_CHAR;
		src_code->output[src_code->output_position++] = ' ';
	}
	if (src_code->current_position > src_code->file_len)
		return (FAIL);
	src_code->output_position -= 2;
	src_code->output[src_code->output_position++] = '\n';
	return (SUCCESS);
}

int				fill_complex_instruction(t_dsm *src_code, t_argum *args)
{
	int op_code;

	op_code = src_code->input[src_code->current_position];
	src_code->current_position += 2;
	if (src_code->current_position >= src_code->file_len)
		return (FAIL);
	write_instruction(src_code, op_code);
	write_args(src_code, args);
	return (SUCCESS);
}
