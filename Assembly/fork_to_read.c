//
// Created by Grass Emerald on 29/02/2020.
//

#include "asm.h"
#include "diz_asm.h"

int asm_s(char *str)
{
	ft_printf("to translate\n");
	return (SUCCESS);
}

int dizasm(char *str)
{
	t_dsm src_code;

	src_code.input = NULL;
	src_code.current_position = 0;
	if (!(src_code.file_len = read_my_binary(str, &src_code.input)))
		return (0);
	return (validate_binary(&src_code));
}