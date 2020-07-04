/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:13:22 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 21:32:39 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			show_mem(t_arena *vm)
{
	print_mem_status(vm);
	if (vm->nice)
		ft_printf("{green}Press ENTER  to continue..{eoc} \n");
	else
		ft_printf("Press ENTER  to continue..\n");
	while (getchar() != '\n')
		;
}

uint32_t		next_step(uint8_t arg_type, t_oper *op)
{
	if (arg_type == T_DIR)
		return (op->size_t_dir);
	else if (arg_type == T_IND)
		return (IND_SIZE);
	else if (arg_type == T_REG)
		return (REG_NAME_SIZE);
	return (0);
}

int32_t			read_mem(t_arena *vm, t_slider *s, uint8_t i, t_oper *op)
{
	int32_t		read;
	int32_t		place;

	read = 0;
	if (s->type_of_args[i - 1] & T_DIR)
		read = bytes_to_magic(vm->map, s->place + s->step, op->size_t_dir);
	else if (s->type_of_args[i - 1] & T_IND)
	{
		place = bytes_to_magic(vm->map, s->place + s->step, IND_SIZE);
		place = op->mod ? (place % IDX_MOD) : place;
		read = bytes_to_magic(vm->map, s->place + place, DIR_SIZE);
	}
	else if (s->type_of_args[i - 1] & T_REG)
		read = s->r[read_byte(vm, s->place, s->step) - 1];
	s->step += next_step(s->type_of_args[i - 1], op);
	return (read);
}
