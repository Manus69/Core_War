/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_instructions_01.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:05:44 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:06:08 by gemerald         ###   ########.fr       */
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
