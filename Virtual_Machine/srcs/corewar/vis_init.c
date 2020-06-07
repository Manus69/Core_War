/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:48:06 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 21:03:45 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			fill_map(t_arena *vm, int32_t place, int32_t l, int32_t p_num)
{
	int32_t		i;
	int32_t		value;

	i = place;
	value = ((p_num - 1) % 4) + 1;
	while (i < l + place)
	{
		vm->viz->map[i].i = value;
		i++;
	}
}

void			init_map(t_arena *vm)
{
	int32_t		place;
	int32_t		id;

	place = 0;
	id = 1;
	while (id <= vm->players)
	{
		fill_map(vm, place, vm->ch[id - 1]->size, id);
		place += MEM_SIZE / vm->players;
		id++;
	}
}

void			init_colors(void)
{
	init_pair(WHITE, COLOR_WHITE, 0);
	init_pair(GREEN, COLOR_GREEN, 0);
	init_pair(YELLOW, COLOR_YELLOW, 0);
	init_pair(RED, COLOR_MAGENTA, 0);
	init_pair(CYAN, COLOR_CYAN, 0);
	init_pair(GRAY_SL, COLOR_BLACK, COLOR_WHITE);
	init_pair(GREEN_SL, COLOR_BLACK, COLOR_GREEN);
	init_pair(YELLOW_SL, COLOR_BLACK, COLOR_YELLOW);
	init_pair(RED_SL, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(CYAN_SL, COLOR_BLACK, COLOR_CYAN);
	init_pair(GREEN_SL, COLOR_BLACK, COLOR_GREEN);
	init_pair(LIGHT_YELLOW, COLOR_WHITE, COLOR_YELLOW);
	init_pair(LIGHT_RED, COLOR_WHITE, COLOR_RED);
	init_pair(LIGHT_CYAN, COLOR_WHITE, COLOR_CYAN);
}

void			init_sl(t_arena *vm)
{
	t_slider	*slider;

	slider = vm->slider;
	while (slider)
	{
		draw_slider(vm, slider);
		if (slider->next)
			slider = slider->next;
		else
			break ;
	}
}

t_viz			*new_viz(t_arena *vm)
{
	t_viz		*new;

	if (!(new = (t_viz *)ft_memalloc(sizeof(t_viz))))
		print_error(MALLOC_ERROR, vm);
	new->win = NULL;
	new->w_info = NULL;
	new->key = 0;
	new->go = 0;
	new->speed = 30;
	new->place = 0;
	new->time = 0;
	return (new);
}
