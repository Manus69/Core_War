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
	char *itoa;
	int file_len;

	input = NULL;
	itoa = NULL;
	i = -1;
	file_len = read_my_binary(str, &input);
	while (++i < file_len)
	{
		itoa = ft_itoa_base((unsigned char)input[i], 16);
		if (itoa[0] == '0')
			ft_printf("00 ");
		else
		{
			if (ft_strlen(itoa) == 1)
				ft_putchar('0');
			ft_printf("%s ", itoa);
		}
		free(itoa);
		if ((i % 64) == 63)
			ft_putchar('\n');
	}
	return (SUCCESS);
}