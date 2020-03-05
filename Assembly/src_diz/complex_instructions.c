//
// Created by Grass Emerald on 05/03/2020.
//

#include "asm.h"

int     write_instruction(t_dsm *src_code, int op_code)
{
	int i;

	i = -1;
	while (op_tab[op_code].op_name[++i])
	{
		src_code->output[src_code->output_position] = op_tab[op_code].op_name[i];
		src_code->output_position++;
	}
	src_code->output[src_code->output_position++] = ' ';
	return (SUCCESS);
}

int    write_reg(t_dsm *src_code, t_argum *args, int j)
{
	char *number;
	int i;

	number = NULL;
	i = -1;
	src_code->output[src_code->output_position++] = 'r';
	if (!(number = ft_itoa(src_code->input[src_code->current_position++])) || !args->arg_type[j])
		return (FAIL);
	while (number[++i])
	{
		src_code->output[src_code->output_position] = number[i];
		src_code->output_position++;
	}
	free(number);
	return (SUCCESS);
}

int    write_ind(t_dsm *src_code, t_argum *args, int j)
{
	char *number;
	int  *value;
	int i;
	int val;
	unsigned char debug;

	number = NULL;
	i = -1;
	if (!(value = (int *)malloc(sizeof(int))))
		return (FAIL);
	*value = 0;
	val = 3;
//	val = 0;
	while (++i < 2)
	{
		((unsigned char*)value)[val] = src_code->input[src_code->current_position];
		debug = src_code->input[src_code->current_position];
		src_code->current_position++;
		val--;
//		val++;
	}
	if (!(number = ft_itoa((*value))) || !args->arg_type[j])
		return (FAIL);
	i = -1;
	while (number[++i])
	{
		src_code->output[src_code->output_position] = number[i];
		src_code->output_position++;
	}
	free(value);
	free(number);
	return (SUCCESS);
}

int    write_dir(t_dsm *src_code, t_argum *args, int j)
{
	char *number;
	int  *value;
	int i;
	int val;
	unsigned char debug;

	number = NULL;
	i = -1;
	if (!(value = (int *)malloc(sizeof(int))))
		return (FAIL);
	val = args->arg_size[j] - 1;
//	val = 0;
	*value = 0;
	while (++i < args->arg_size[j])
	{
		((unsigned char*)value)[val] = src_code->input[src_code->current_position];
		debug = src_code->input[src_code->current_position];
		src_code->current_position++;
		val--;
//		val++;
	}
	if (!(number = ft_itoa((*value))) || !args->arg_type[j])
		return (FAIL);
	i = -1;
	src_code->output[src_code->output_position++] = DIRECT_CHAR;
	while (number[++i])
	{
		src_code->output[src_code->output_position] = number[i];
		src_code->output_position++;
	}
	free(value);
	free(number);
	return (SUCCESS);
}

static void     init_functions_args(int (*actions[])(t_dsm *, t_argum *, int))
{
	actions[0] = NULL;
	actions[1] = &write_reg;
	actions[2] = &write_dir;
	actions[3] = &write_ind;
}

int     write_args(t_dsm *src_code, t_argum *args)
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

int     fill_complex_instruction(t_dsm *src_code, t_argum *args)
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