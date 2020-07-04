/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_13_16.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:07:39 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 21:05:41 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			lld(t_arena *vm, t_slider *sl)
{
	int32_t		value;
	int32_t		r_id;

	sl->step += 1;
	value = read_mem(vm, sl, 1, (t_oper *)&g_operation_list[sl->code - 1]);
	sl->carry = value == 0 ? 1 : 0;
	r_id = read_byte(vm, sl->place, sl->step);
	sl->r[r_id - 1] = value;
	sl->step += REG_NAME_SIZE;
}

void			lldi(t_arena *vm, t_slider *sl)
{
	int32_t		addr_1;
	int32_t		addr_2;
	int32_t		r_id;

	sl->step += 1;
	addr_1 = read_mem(vm, sl, 1, (t_oper *)&g_operation_list[sl->code - 1]);
	addr_2 = read_mem(vm, sl, 2, (t_oper *)&g_operation_list[sl->code - 1]);
	r_id = read_byte(vm, sl->place, sl->step);
	sl->r[r_id - 1] = bytes_to_magic(vm->map,
			sl->place + (addr_1 + addr_2), DIR_SIZE);
	sl->step += REG_NAME_SIZE;
}

void			lfork(t_arena *vm, t_slider *sl)
{
	int32_t		addr;
	t_slider	*new;

	new = NULL;
	addr = read_mem(vm, sl, 1, (t_oper *)&g_operation_list[sl->code - 1]);
	if ((new = copy_slider(vm, sl, addr)))
		new->next = vm->slider;
	vm->slider = new;
	vm->num_slider++;
}

void			aff(t_arena *vm, t_slider *sl)
{
	int32_t		r_id;
	int32_t		value;

	sl->step += 1;
	r_id = read_byte(vm, sl->place, sl->step);
	value = sl->r[r_id - 1];
	sl->step += REG_NAME_SIZE;
	if (vm->aff_print)
		ft_printf("{green}Operaions aff says: %c{eoc} \n", (char)value);
	if (vm->visual)
	{
		vm->viz->aff = (char)value;
		vm->viz->aff_champ = sl->player;
	}
}
