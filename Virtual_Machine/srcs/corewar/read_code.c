/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:09:12 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 21:03:11 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int					is_register(t_arena *vm, int32_t place, int32_t step)
{
	int8_t			r_id;

	r_id = read_byte(vm, place, step);
	return (r_id >= 1 && r_id <= REG_NUMBER);
}

int					check_reg(t_slider *cursor, t_arena *vm, t_oper *op)
{
	unsigned int	i;
	uint32_t		step;

	i = 0;
	step = (1 + (op->read_args ? 1 : 0));
	while (i < op->args_num)
	{
		if ((cursor->type_of_args[i] == T_REG)
			&& !is_register(vm, cursor->place, step))
			return (0);
		step += next_step(cursor->type_of_args[i], op);
		i++;
	}
	return (1);
}

int8_t				read_args(t_arena *vm, int32_t place, int32_t step)
{
	int32_t			index;
	int8_t			read;

	index = find_place(place + step);
	read = vm->map[index];
	return (read);
}

int					compare_args(t_slider *sl, t_oper *op)
{
	unsigned int	i;

	i = 0;
	while (i < op->args_num)
	{
		if (!(sl->type_of_args[i] & op->args_type[i]))
			return (0);
		i++;
	}
	return (1);
}

void				read_args_size(t_arena *vm, t_slider *s, t_oper *op)
{
	int8_t			byte;

	byte = 0;
	if (op->read_args != 0)
		byte = read_args(vm, s->place, 1);
	s = write_args_types(s, op, byte);
	if (compare_args(s, op) && check_reg(s, vm, op))
	{
		s->step += 1;
		op->operation(vm, s);
		s->write = 0;
	}
	else
		s->step += step(s, op);
}
