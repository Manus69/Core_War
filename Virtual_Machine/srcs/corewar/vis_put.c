/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:48:06 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 21:03:45 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			get_live_color(t_champ *player)
{
	int32_t			index;

	index = ((player->num - 1) % 4) + 1;
	if (index == 1)
		return (COLOR_PAIR(19) | A_BOLD);
	else if (index == 1 + 1)
		return (COLOR_PAIR(20) | A_BOLD);
	else if (index == 1 + 2)
		return (COLOR_PAIR(21) | A_BOLD);
	else
		return (COLOR_PAIR(22) | A_BOLD);
}

int					get_attribute(t_arena *vm, t_data *info, ssize_t cycles)
{
	if (cycles != vm->cycles && vm->death > 0 && info->wait_live > 0)
		info->wait_live--;
	if (cycles != vm->cycles && vm->death > 0 && info->wait_store > 0)
		info->wait_store--;
	if (info->wait_live)
		return (get_live_color(info->live));
	else if (info->wait_store)
		return (g_color_palette[info->i] | A_BOLD);
	else
		return (g_color_palette[info->i]);
}

static void			draw_arena(t_arena *vm)
{
	static ssize_t	cycles = 0;
	int				i;
	int				j;
	int				attribute;

	i = 0;
	while (i < 64)
	{
		j = 0;
		wmove(vm->viz->win, i + 2, 5);
		while (j < 64)
		{
			attribute = get_attribute(vm, &vm->viz->map[i * 64 + j], cycles);
			wattron(vm->viz->win, attribute);
			wprintw(vm->viz->win, "%.2x", vm->map[i * 64 + j]);
			wattroff(vm->viz->win, attribute);
			waddch(vm->viz->win, ' ');
			j++;
		}
		wprintw(vm->viz->win, "\n");
		i++;
	}
	cycles = vm->cycles;
}

static void			draw_border(t_arena *vm)
{
	int			i;

	i = 1;
	wattron(vm->viz->win, COLOR_PAIR(WHITE));
	while (i < 67)
	{
		mvwprintw(vm->viz->win, i, 0, "*");
		mvwprintw(vm->viz->win, i, 200, "*");
		i++;
	}
	i = 0;
	while (i < 241)
	{
		mvwprintw(vm->viz->win, 1, i, "*");
		mvwprintw(vm->viz->win, 67, i, "*");
		++i;
	}
	wattroff(vm->viz->win, COLOR_PAIR(WHITE));
}

void				draw(t_arena *vm)
{
	werase(vm->viz->win);
	werase(vm->viz->w_info);
	draw_arena(vm);
	draw_info(vm);
	draw_border(vm);
	wrefresh(vm->viz->w_info);
	wrefresh(vm->viz->win);
}
