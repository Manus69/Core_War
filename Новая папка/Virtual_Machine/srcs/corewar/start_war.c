# include "corewar.h"

void	read_next_byte(t_arena *vm, t_slider *move, int32_t place)
{
	uint8_t read;

	read = vm->map[place];
	move->code = read;
	move->cool_down = is_op(read) ? operation_list[move->code - 1].cool_down : move->cool_down;
}

void 	dump_mem(t_arena *vm)
{
	print_mem_status(vm); 		// печать состояния памяти
	free_arena(&vm); 			// очищаем память
	exit(0); 					// выходим
}

void 	show_mem(t_arena *vm)
{
	print_mem_status(vm); 													// печатаем состояние памяти
	ft_printf("{green}Press ENTER  to continue..{eoc} \n");			// сообщаем, что для проделжения нужно нажать ENTER
	while (getchar() != '\n')
		;		// ждем ENTER
}

void	rw_memory(t_arena *vm, t_slider *sl, int sliders, t_operation *op)
{
	int i;

	while (sl && sliders--) 														// работаем со всеми каретками по очереди
	{
		if (sl->cool_down == 0) 											// если оперция выполнена или мы только начинаем
			read_next_byte(vm, sl, sl->place);								//считываем байт
		if (sl->cool_down > 0)												// если есть задержка операции
			sl->cool_down--; 												// уменьшаем время ожидания операции
		if (sl->cool_down == 0) 											// если пришло время выполнения операции
		{
			op = NULL;
			op = is_op(sl->code) ? &operation_list[sl->code - 1] : op; // выбираем шаблон нужной операцию
			if (op) // если у нас считана операция
				read_args_size(vm, sl, op);
			else //если не операция тогда переходим на след байт
				sl->step++;
			i = 0;
			if (vm->visual)
				clear_slider(vm, sl);
			sl->place += sl->step;
			sl->place = find_place(sl->place);
			if (vm->visual)
				draw_slider(vm, sl);
			sl->step = 0;
			while (i < 3)
				sl->type_of_args[i++] = 0;
		}
		sl = sl->next;
	}
}

void	start_war(t_arena  *vm)
{
	t_operation		*op;

	op = NULL;
	while (vm->num_slider) //играем до смерти всех кареток
	{
		if (vm->d_dump != 0 && vm->d_dump == vm->cycles) // если есть флаги -d или -dump
			dump_mem(vm);
		if (vm->show > 0 && vm->cycles % vm->show == 0) //если есть флаг -s
			show_mem(vm);
		vm->cycles += 1; //увеличиваем количество циклов на 1, пошел первый цикл
		vm->c_after_check += 1; //увеличиваем количество циклов после проверки на 1
		rw_memory(vm, vm->slider, vm->num_slider, op); // читает команду коретки и если приходит время операции выполняет код
		if (vm->death_coming == vm->c_after_check || vm->death_coming <= 0) //
			cycles_to_die_check(vm);
	}
	ft_printf(":smile_14 {red}Contesant %d", vm->last_alive->number);
	ft_printf(",{Lblue} %s,{green} has won!{eoc} \n", vm->last_alive->name);//печать победителя
}