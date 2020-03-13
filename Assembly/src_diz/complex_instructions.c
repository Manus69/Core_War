/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_instructions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:24:07 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:29:18 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				write_instruction(t_dsm *src_code, int op_code)
{
	int i;

	i = -1;
	while (g_op_tab[op_code].op_name[++i])
	{
		src_code->output[src_code->output_position] =\
							g_op_tab[op_code].op_name[i];
		src_code->output_position++;
	}
	src_code->output[src_code->output_position++] = ' ';
	return (SUCCESS);
}

int				write_reg(t_dsm *src_code, t_argum *args, int j)
{
	char	*number;
	int		i;

	number = NULL;
	i = -1;
	src_code->output[src_code->output_position++] = 'r';
	if (!(number =\
	ft_itoa(src_code->input[src_code->current_position++])) ||
			!args->arg_type[j])
		return (FAIL);
	while (number[++i])
	{
		src_code->output[src_code->output_position] = number[i];
		src_code->output_position++;
	}
	free(number);
	return (SUCCESS);
}

char			*take_short_dir(t_dsm *src_code)
{
	int			val;
	int			i;
	short int	*value_short;
	char		*itoa;

	if (!(value_short = (short int *)malloc(sizeof(short int))))
		return (NULL);
	val = 1;
	i = -1;
	*value_short = 0;
	while (++i < 2)
	{
		((unsigned char*)value_short)[val] =\
							src_code->input[src_code->current_position];
		src_code->current_position++;
		val--;
	}
	itoa = ft_itoa(*value_short);
	free(value_short);
	return (itoa);
}

char			*take_simple_dir(t_dsm *src_code)
{
	int		val;
	int		i;
	int		*value;
	char	*itoa;

	if (!(value = (int *)malloc(sizeof(int))))
		return (NULL);
	val = 3;
	i = -1;
	*value = 0;
	while (++i < 4)
	{
		((unsigned char*)value)[val] =\
					src_code->input[src_code->current_position];
		src_code->current_position++;
		val--;
	}
	itoa = ft_itoa(*value);
	free(value);
	return (itoa);
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
	actions[3] = &write_dir;
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
