/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_war.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:14:42 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 21:35:56 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			read_next_byte(t_arena *vm, t_slider *move, int32_t place)
{
	uint8_t read;

	read = vm->map[place];
	move->code = read;
	move->cool_down = is_op(read) ?
			g_operation_list[move->code - 1].cool_down : move->cool_down;
}

void			dump_mem(t_arena *vm)
{
	print_mem_status(vm);
	free_arena(&vm);
	exit(0);
}

void			do_operation(t_oper *op, t_slider *sl, t_arena *vm)
{
	int i;

	op = NULL;
	op = is_op(sl->code) ? (t_oper *)&g_operation_list[sl->code - 1] : op;
	if (op)
		read_args_size(vm, sl, op);
	else
		sl->step++;
	i = 0;
	if (vm->visual)
		clear_slider(vm, sl);
	sl->place += sl->step;
	sl->place = find_place(sl->place);
	if (vm->visual)
		draw_slider(vm, sl);
	sl->step = 0;
	while (i < 3)
		sl->type_of_args[i++] = 0;
}

void			rw_memory(t_arena *vm, t_slider *sl, int slide, t_oper *op)
{
	while (sl && slide--)
	{
		if (sl->cool_down == 0)
			read_next_byte(vm, sl, sl->place);
		if (sl->cool_down > 0)
			sl->cool_down--;
		if (sl->cool_down == 0)
			do_operation(op, sl, vm);
		sl = sl->next;
	}
}

void			start_war(t_arena *vm)
{
	t_oper	*op;

	op = NULL;
	while (vm->num_slider)
	{
		if (vm->d_dump != 0 && vm->d_dump == vm->cycles)
			dump_mem(vm);
		if (vm->show > 0 && vm->cycles % vm->show == 0)
			show_mem(vm);
		vm->cycles += 1;
		vm->c_after_check += 1;
		rw_memory(vm, vm->slider, vm->num_slider, op);
		if (vm->death == vm->c_after_check || vm->death <= 0)
			cycles_to_die_check(vm);
	}
	if (vm->nice)
	{
		ft_printf(":smile_14 {red}Contesant %d", vm->last->num);
		ft_printf(",{Lblue} \"%s\",{green} has won!{eoc} \n", vm->last->name);
	}
	else
	{
		ft_printf("Contesant %d", vm->last->num);
		ft_printf(", \"%s\", has won!\n", vm->last->name);
	}
}
