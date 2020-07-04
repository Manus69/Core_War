/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 16:43:06 by selly             #+#    #+#             */
/*   Updated: 2020/07/03 17:52:00 by gemerald         ###   ########.fr       */
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

int				check_players_num(t_arena *vm, int players)
{
	t_champ	*buf;

	buf = NULL;
	if ((vm->players == 0 || players == 0))
		print_error(PLAYER_ERROR, vm);
	else if ((buf = vm->champion) != NULL && players > 0)
	{
		while (buf != NULL)
		{
			if (players < buf->num)
				print_error(PLAYER_ID_ERROR, vm);
			buf = buf->next;
		}
	}
	return (1);
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
	t_champ		*last;

	if (vm->print_type == 0)
		vm->print_type = 1;
	check_players_num(vm, vm->players);
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
