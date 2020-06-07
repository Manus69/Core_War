/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:29:56 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 20:58:21 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		draw_slider(t_arena *vm, t_slider *sl)
{
	if (vm->viz->map[sl->place].i >= 0 && vm->viz->map[sl->place].i <= 4)
		vm->viz->map[sl->place].i = (vm->viz->map[sl->place].i) + 5;
}

void		put_data(t_arena *vm)
{
	initscr();
	noecho();
	nodelay(stdscr, true);
	curs_set(0);
	use_default_colors();
	start_color();
	init_colors();
	init_map(vm);
	vm->viz->win = newwin(MEM_SIZE / 64 + 4, (64 * 3 + 5) + 4, 1, 2);
	vm->viz->w_info = newwin(MEM_SIZE / 64 + 4, (64 * 3 + 5) /
	4 + 10, 1, (64 * 3 + 5) + 6);
	init_sl(vm);
}
