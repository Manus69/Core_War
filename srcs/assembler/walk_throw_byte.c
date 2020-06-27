/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walk_throw_byte.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:38:59 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:45:09 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		set_args_size(int arg_type, int *arg_size, int size_t_dir)
{
	if (arg_type == REG_CODE)
		*arg_size = 1;
	else if (arg_type == IND_CODE)
		*arg_size = IND_SIZE;
	else if (arg_type == DIR_CODE)
	{
		if (size_t_dir)
			*arg_size = 2;
		else
			*arg_size = DIR_SIZE;
	}
	else
		return (FAIL);
	return (SUCCESS);
}

int		take_args(unsigned char arg_type_byte, t_argum *args, int size_t_dir)
{
	int i;

	i = -1;
	ft_bzero(args, sizeof(t_argum));
	args->args_count = 0;
	args->arg_type[0] = (arg_type_byte & 0xC0) >> 6;
	args->arg_type[1] = (arg_type_byte & 0x30) >> 4;
	args->arg_type[2] = (arg_type_byte & 0xC) >> 2;
	while (++i < 3)
	{
		if (args->arg_type[i])
		{
			if (!(set_args_size(args->arg_type[i], &args->arg_size[i],\
							size_t_dir)))
				return (FAIL);
			args->args_count++;
		}
	}
	return (SUCCESS);
}

int		walk_throw(t_dsm *src_code)
{
	t_argum args;

	while (src_code->current_position < src_code->file_len)
	{
		if (src_code->input[src_code->current_position] > 16 ||
			src_code->input[src_code->current_position] < 1)
			return (FAIL);
		if (g_op_tab[src_code->input[src_code->current_position]].arg_code_flag)
		{
			take_args(src_code->input[src_code->current_position + 1], &args,\
				g_op_tab[src_code->input[src_code->current_position]].\
				size_t_dir);
			fill_complex_instruction(src_code, &args);
		}
		else
			fill_simple_instruction(src_code);
	}
	src_code->output[src_code->output_position] = '\0';
	return (SUCCESS);
}
