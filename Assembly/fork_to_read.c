//
// Created by Grass Emerald on 29/02/2020.
//

#include "asm.h"

int asm_s(char *str)
{
	ft_printf("to translate\n");
	return (SUCCESS);
}

int dizasm(char *str)
{
	char *input;
	int i;

	input = NULL;
	i = -1;
	read_my_binary(str, &input);
	while (++i < 3185)
	{
		ft_printf("%#x ", (char *)input[i]);
	}
	return (SUCCESS);
}