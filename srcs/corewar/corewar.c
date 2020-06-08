/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:43:06 by selly             #+#    #+#             */
/*   Updated: 2020/06/01 16:43:48 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_arena			*fill_arena(t_arena *vm, int players, int x)
{
	int			count;
	int			a;
	int			i;
	int			index;

	count = 1;
	index = 0;
	while (count <= players)
	{
		a = index;
		i = 0;
		while (i < vm->ch[x]->size)
		{
			vm->map[a] = vm->ch[x]->code[i];
			vm->color[a] = vm->ch[x]->num;
			i++;
			a++;
		}
		count++;
		index += MEM_SIZE / players;
		x++;
	}
	return (vm);
}

t_arena			*get_slider(t_arena *vm)
{
	int			i;
	int			place;
	t_slider	*sl;
	t_slider	*buf;

	i = 0;
	place = 0;
	buf = NULL;
	while (i < vm->players)
	{
		if (i != 0)
			buf = sl;
		sl = init_slider(vm, i, place, 1);
		vm->slider = sl;
		vm->slider->next = buf;
		vm->num_slider += 1;
		place += MEM_SIZE / vm->players;
		i++;
	}
	return (vm);
}

t_arena			*ready_to_start(t_arena *vm)
{
	int			i;
	t_champ	*last;

	if (vm->print_type == 0)
		vm->print_type = 1;
	last = vm->champion;
	i = 0;
	while (i < vm->players)
	{
		vm->ch[last->num - 1] = last;
		last = last->next;
		i++;
	}
	if (!vm->visual)
		inroduction(vm->ch, vm->players, vm->nice, 0);
	vm = fill_arena(vm, vm->players, 0);
	vm = get_slider(vm);
	return (vm);
}

int				main(int argc, char **argv)
{
	t_arena		*vm;

	vm = init_arena();
	if (argc >= 2)
	{
		vm = check_input(argv, argc - 1, vm);
		vm = ready_to_start(vm);
		if (!vm->visual)
			start_war(vm);
		else
			show_war(vm);
	}
	else
		usage(0, 0);
	free_arena(&vm);
	return (0);
}
