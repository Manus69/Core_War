//
// Created by Grass Emerald on 03/03/2020.
//

#include "asm.h"

int     err_output(t_dsm *src_code)
{
	free(src_code->input);
	free(src_code->output);
	ft_putstr_fd("ERROR : CAN'T FILL OUTPUT", 2);
	return (FAIL);
}

int     collect_pre_print(t_dsm *src_code)
{
	if (!(src_code->output = ft_strnew(OUTPUT_LEN)))
		return (FAIL);
	src_code->output_position = 0;
	if (!(put_name_comment(src_code)))
		return (err_output(src_code));
	return (SUCCESS);
}