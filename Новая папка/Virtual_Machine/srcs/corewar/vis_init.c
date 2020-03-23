#include "corewar.h"

static void	fill_map(t_arena *vm, int32_t place, int32_t l, int32_t player_num)
{
	int32_t i;
	int32_t value;

	i = place;
	value = ((player_num - 1) % 4) + 1;
	while (i < l + place)
	{
		vm->viz->map[i].i = value;
		i++;
	}
}

static void	init_map(t_arena *vm)
{
	int32_t	place;
	int32_t	id;

	place = 0;
	id = 1;
	while (id <= vm->players)
	{
		fill_map(vm, place, vm->ch[id - 1]->pl_size, id);
		place += MEM_SIZE / vm->players;
		id++;
	}
}

void	draw_slider(t_arena *vm, t_slider *sl)
{
	if (vm->viz->map[sl->place].i >= 0
		&& vm->viz->map[sl->place].i <= 4)
		vm->viz->map[sl->place].i =
				(vm->viz->map[sl->place].i) + 5;
}

void		init_colors(void)
{
	// Цветовая пара состоит из переднего плана (цвета для символов) и цвета фона (для пустого поля, на котором отображается символы).
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

void	init_sl(t_arena *vm)
{
	t_slider *slider;

	slider = vm->slider;
	while (slider)
	{
		draw_slider(vm, slider);
		if (slider->next)
			slider = slider->next;
		else
			break;
	}
}

void		put_data(t_arena *vm)
{
	initscr(); 					// переводит терминал в curses-режим
	nodelay(stdscr, true);		// вызов приводит к тому, что getch является неблокирующим вызовом. Если выход не готов, getch возвращает ERR.
	curs_set(0);				// установка курсора в невидимое - 0, нормальное - 1 или очень видимое - 2 состояние
	use_default_colors();		// делает прозрачность доступной и не нужно самим настраивать атрибуты цвета
	start_color();				// должен быть вызван , если будем использовать цвета
	init_colors();				// выше - определяем необходимые цвета
	init_map(vm);
	vm->viz->win = newwin(MEM_SIZE / 64 + 4, (64 * 3 + 5) + 4, 1, 2);	//	создаем окно для игры
	vm->viz->w_info = newwin(MEM_SIZE / 64 + 4, (64 * 3 + 5) / 4 + 10, 1, (64 * 3 + 5) + 6);	//	окно для инфы справа
	init_sl(vm);
}

t_viz	*new_viz(t_arena *vm)
{
	t_viz	*new;

	if (!(new = (t_viz *)ft_memalloc(sizeof(t_viz))))
		print_error(MALLOC_ERROR, vm);
	new->win = NULL;
	new->w_info = NULL;
	new->key = 0;
	new->go = 0;
	new->speed = 30;
	new->place = 0;
	new->time = 0;
	new->sound = 0;
	return (new);
}