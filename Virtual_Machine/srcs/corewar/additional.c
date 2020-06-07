/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:48:03 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 11:48:42 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				is_op(int8_t byte)
{
	return (byte >= 0x01 && byte <= 0x10);
}

void			find_op(int8_t arg_type, int8_t index, t_slider *sl)
{
	sl->type_of_args[index - 1] = g_arg_code[arg_type - 1];
}

t_slider		*write_args_types(t_slider *s, t_oper *op, int8_t code)
{
	if (op->read_args)
	{
		if (op->args_num >= 1)
			find_op((int8_t)((code & 0xC0) >> 6), 1, s);
		if (op->args_num >= 2)
			find_op((int8_t)((code & 0x30) >> 4), 2, s);
		if (op->args_num >= 3)
			find_op((int8_t)((code & 0xC) >> 2), 3, s);
	}
	else
		s->type_of_args[0] = op->args_type[0];
	return (s);
}

int8_t			read_byte(t_arena *vm, int32_t place, int32_t step)
{
	int32_t		index;
	uint8_t		read;

	index = find_place(place + step);
	read = vm->map[index];
	return (read);
}

t_slider		*copy_slider(t_arena *vm, t_slider *sl, int32_t addr)
{
	t_slider	*new;
	int			i;

	addr = find_place(sl->place + addr);
	new = init_slider(vm, 0, addr, 0);
	i = 0;
	while (i < REG_NUMBER)
	{
		new->r[i] = sl->r[i];
		i++;
	}
	new->carry = sl->carry;
	new->last_live = sl->last_live;
	new->player = sl->player;
	return (new);
}
