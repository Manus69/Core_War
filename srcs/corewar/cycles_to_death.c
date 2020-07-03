/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles_to_death.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 02:35:02 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 14:24:20 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		reset_lives_nums(t_arena *vm)
{
	int32_t		i;

	i = 0;
	while (i < vm->players)
	{
		vm->ch[i]->lives_before = vm->ch[i]->live;
		vm->ch[i]->live = 0;
		i++;
	}
	vm->lives = 0;
}

int				is_died(t_arena *vm, t_slider *cursor)
{
	return (vm->death <= 0 ||
	vm->cycles - cursor->last_live >= vm->death);
}

static void		delete_died_cursors(t_arena *vm)
{
	t_slider	*previous;
	t_slider	*current;
	t_slider	*delete;

	previous = NULL;
	current = vm->slider;
	delete = NULL;
	while (current)
		if (is_died(vm, (delete = current)) && vm->num_slider--)
		{
			current = current->next;
			if (vm->slider == delete)
				vm->slider = current;
			if (previous)
				previous->next = current;
			ft_memdel((void **)&delete);
		}
		else
		{
			previous = current;
			current = current->next;
		}
}

void			cycles_to_die_check(t_arena *vm)
{
	vm->checks++;
	delete_died_cursors(vm);
	if (vm->checks == MAX_CHECKS || vm->lives >= NBR_LIVE)
	{
		vm->death -= CYCLE_DELTA;
		vm->checks = 0;
	}
	reset_lives_nums(vm);
	vm->c_after_check = 0;
}
