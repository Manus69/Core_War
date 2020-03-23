#include "corewar.h"

void	draw_slider(t_arena *vm, t_slider *sl)
{
	if (vm->viz->map[sl->place].i >= 0 && vm->viz->map[sl->place].i <= 4)
		vm->viz->map[sl->place].i = (vm->viz->map[sl->place].i) + 5;
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