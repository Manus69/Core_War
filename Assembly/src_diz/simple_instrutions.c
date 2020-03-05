//
// Created by Grass Emerald on 05/03/2020.
//

#include "asm.h"

int    write_simple_dir(t_dsm *src_code, int size_t_dir)
{
	char *number;
	short int  *value;
	int i;
	int val;

	number = NULL;
	i = -1;
	if (!(value = (unsigned short int *)malloc(sizeof(short int))))
		return (FAIL);
	val = size_t_dir - 1;
//	val = 0;
	*value = 0;
	while (++i < size_t_dir)
	{
		((unsigned char*)value)[val] = src_code->input[src_code->current_position];
		src_code->current_position++;
		val--;
//		val++;
	}
//	*value -= 1;
//	*value = ~(*value);
	if (!(number = ft_itoa((*value))))
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

int     fill_simple_instruction(t_dsm *src_code)
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
	write_simple_dir(src_code, size_t_dir);
	src_code->output[src_code->output_position++] = '\n';
	return (SUCCESS);
}