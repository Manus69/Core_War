#include "corewar.h"

void	draw_exec_status(t_arena *vm)
{
	vm->viz->place = 2;
	if (vm->viz->go)
	{
		wattron(vm->viz->w_info, COLOR_PAIR(CYAN));
		mvwprintw(vm->viz->w_info, vm->viz->place, BORDER, "%-10s", "PLAY >>>>");
		wattroff(vm->viz->w_info, COLOR_PAIR(CYAN));
	}
	else
	{
		wattron(vm->viz->w_info, A_BLINK);
		wattron(vm->viz->w_info, COLOR_PAIR(YELLOW));
		mvwprintw(vm->viz->w_info, vm->viz->place, BORDER, "%-10s", (vm->num_slider) ? "** PAUSED **" : "** STOPPED **");
		wattroff(vm->viz->w_info, COLOR_PAIR(YELLOW));
		wattroff(vm->viz->w_info, A_BLINK);
	}
}

void		draw_info(t_arena *vm)
{
	wattron(vm->viz->w_info, A_BOLD);
	draw_exec_status(vm);
	mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "Cycles/second : %d", vm->viz->speed);
	mvwprintw(vm->viz->w_info, vm->viz->place += 3, BORDER, "Cycle : %zd", vm->cycles);
	mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "Cursors : %zu", vm->num_slider);
	if (vm->viz->sound)
		mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "Sound ON");
	else
		mvwprintw(vm->viz->w_info, vm->viz->place += 2, BORDER, "Sound OFF");
	draw_players(vm);
	draw_menu(vm);
	if (vm->viz->aff_champ)
		draw_aff(vm);
	if (!vm->num_slider)
		draw_winner(vm);
	wattroff(vm->viz->w_info, A_BOLD);
}

void	play_sound(t_arena *vm, char flag)
{
	if (vm->viz->sound && flag == 'v')
	{
		system("pkill afplay");
		system("afplay ./srcs/corewar/sounds/win.mp3");
	}
	else if (vm->viz->sound && flag == 'd')
	{
		system("pkill afplay");
		system("afplay ./srcs/corewar/sounds/death.mp3");
	}
	else if (vm->viz->sound && flag == 'p')
	{
		system("pkill afplay");
		system("afplay ./srcs/corewar/sounds/game.mp3");
	}
}

static void	vis_start_war(t_arena *vm)
{
	t_operation		*op;

	op = NULL;
	if (vm->num_slider)
	{
		vm->cycles += 1;
		vm->c_after_check += 1;
		rw_memory(vm, vm->slider, vm->num_slider, op);
		if (vm->death_coming == vm->c_after_check || vm->death_coming <= 0) //
			cycles_to_die_check(vm);
		if (!vm->num_slider)
			vm->viz->go = 0;
	}
}

void	show_war(t_arena *vm)
{
	vm->d_dump = 0;
	vm->show = 0;
	vm->aff_print = 0;
	vm->viz = new_viz(vm);
	put_data(vm);
	while ((vm->viz->key = getch()) != 27)
	{
		set_key(vm); //устанавливаем управление и проверяем константы
		if (vm->viz->go && (clock() >= vm->viz->time + CLOCKS_PER_SEC / vm->viz->speed))
		{
			vm->viz->time = clock();
			vis_start_war(vm);
		}
		draw(vm);
	}
	endwin(); // выключает окошко
	curs_set(1); //возвращает обычную настройку курсора
}