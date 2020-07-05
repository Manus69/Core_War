/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_5_8.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:02:11 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 20:51:46 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		bin_op(t_arena *vm, t_slider *sl, int op)
{
	int32_t	value_1;
	int32_t	value_2;
	int32_t	value;
	int32_t	r_id;

	sl->step += 1;
	value_1 = read_mem(vm, sl, 1, (t_oper *)&g_operation_list[sl->code - 1]);
	value_2 = read_mem(vm, sl, 2, (t_oper *)&g_operation_list[sl->code - 1]);
	value = 0;
	if (op == 1)
		value = value_1 & value_2;
	else if (op == 2)
		value = value_1 | value_2;
	else if (op == 3)
		value = value_1 ^ value_2;
	sl->carry = value == 0 ? 1 : 0;
	r_id = read_byte(vm, sl->place, sl->step);
	sl->r[r_id - 1] = value;
	sl->step += REG_NAME_SIZE;
}

void		sub(t_arena *vm, t_slider *sl)
{
	int32_t	reg1;
	int32_t	reg2;
	int32_t	reg3;
	int32_t	value;

	sl->step += 1;
	reg1 = read_byte(vm, sl->place, sl->step);
	sl->step += REG_NAME_SIZE;
	reg2 = read_byte(vm, sl->place, sl->step);
	sl->step += REG_NAME_SIZE;
	value = sl->r[reg1 - 1] - sl->r[reg2 - 1];
	sl->carry = value == 0 ? 1 : 0;
	reg3 = read_byte(vm, sl->place, sl->step);
	sl->r[reg3 - 1] = value;
	sl->step += REG_NAME_SIZE;
}

void		and(t_arena *vm, t_slider *sl)
{
	bin_op(vm, sl, 1);
}

void		or(t_arena *vm, t_slider *sl)
{
	bin_op(vm, sl, 2);
}

void		xor(t_arena *vm, t_slider *sl)
{
	bin_op(vm, sl, 3);
}
