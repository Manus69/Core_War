//
// Created by Grass Emerald on 03/03/2020.
//

#include "asm.h"

int     take_args(unsigned char arg_type_byte, t_argum *args)
{
	ft_bzero(args, sizeof(t_argum));
	args->arg_type[0] = (arg_type_byte & 0xC0) >> 6;
	args->arg_type[1] = (arg_type_byte & 0x30) >> 4;
	args->arg_type[2] = (arg_type_byte & 0xC) >> 2;
	return (SUCCESS);
}

//0xC0 for 1st arg
//0x30 for 2nd arg
//0xC for 3d arg

int     walk_throw(t_dsm *src_code)
{
	unsigned char octet = 104;
	unsigned char alfa;
	t_argum args;

	octet = src_code->input[src_code->current_position + 1];
	alfa = (octet & 0xC) >> 2;
	ft_printf("octet = %s alfa = %d\n", ft_itoa_base(octet, 16), alfa);
	take_args(src_code->input[src_code->current_position + 1], &args);
//	t_argum args;
//
//	while (src_code->current_position < src_code->file_len)
//	{
//
//	}
	ft_putstr(op_tab[src_code->input[src_code->current_position]].op_descript);
//	print_alone_byte(src_code);
}