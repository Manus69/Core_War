#include "corewar.h"

void	draw_players(t_arena *vm)
{
	int32_t i;


	i = 0;
	vm->viz->place += 1;
	while (i < vm->players)
	{
		mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "Player - %d : \n", vm->ch[i]->number);
		wattron(vm->viz->w_info, color_palette[vm->ch[i]->number]);
		mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "%.38s\n", vm->ch[i]->name);
		wattroff(vm->viz->w_info, color_palette[vm->ch[i]->number]);
		mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "%-32s %d", "   Last live :", vm->ch[i]->last_live);
		mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "%-32s %d", "   Lives in current period :", vm->ch[i]->live);
		i++;
	}
}

void	draw_menu(t_arena *vm) {
	mvwprintw(vm->viz->w_info, vm->viz->place += 3, BORDER, "%-15s %d", "Cycle to die :", vm->death_coming);
	mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "%-15s %d", "Cycle delta :", CYCLE_DELTA);
	mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "%-15s %d/%d", "Lives :", vm->lives, NBR_LIVE);
	mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "%-15s %d", "Cycles to check :",
			  (vm->death_coming > 0) ? vm->death_coming - vm->c_after_check : 0);
	mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "%-15s %d/%d", "Checks :", vm->checks, MAX_CHECKS);
	wattron(vm->viz->w_info, color_palette[2]);
	mvwprintw(vm->viz->w_info, vm->viz->place += 3, BORDER, "Help:");
	wattroff(vm->viz->w_info, color_palette[2]);
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "SPACE - pause");
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "ESC - exit");
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "\"s\" - sound off/on");
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "\"1\" - speed + 10");
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "\"2\" - speed + 100");
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "\"3\" - speed - 10");
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "\"4\" - speed - 100");
	mvwprintw(vm->viz->w_info, vm->viz->place += 1, BORDER, "\"5\" - default speed");
}

void	draw_aff(t_arena *vm)
{
	int32_t i;

	i = ((vm->viz->aff_champ->number - 1) % 4) + 1;
	mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "%-15s ", "Aff value :");
	wattron(vm->viz->w_info, color_palette[i]);
	wprintw(vm->viz->w_info, "%d", vm->viz->aff);
	if (ft_isprint(vm->viz->aff))
		wprintw(vm->viz->w_info, " '%c'", vm->viz->aff);
	wattroff(vm->viz->w_info, color_palette[i]);
}

void	draw_winner(t_arena *vm)
{
	vm->viz->place = (vm->viz->place + (MEM_SIZE / 64 + 4) - 3) / 2;
	mvwprintw(vm->viz->w_info, vm->viz->place, BORDER, "The winner is ");
	wattron(vm->viz->w_info, color_palette[vm->last_alive->number]);
	wprintw(vm->viz->w_info, "%.36s", vm->last_alive->name);
	wattroff(vm->viz->w_info, color_palette[vm->last_alive->number]);
	play_sound(vm, 'v');
}