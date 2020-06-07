#include "corewar.h"

void	inroduction(t_arena *head, int count)
{
	int		i;

	i = 0;
	ft_printf("{green}Introducing contestants...{eoc}\n");
	while (i < count)
	{
		if (i + 1 == 1)
			ft_printf("{red}* :smile_1  ");
		else if (i + 1 == 2)
			ft_printf("{red}* :smile_7  ");
		else if (i + 1 == 3)
			ft_printf("{red}* :smile_5  ");
		else if (i + 1 == 4)
			ft_printf("{red}* :smile_8  ");
		ft_printf("Player %d: {blue}weighing %d bytes, ", head->ch[i]->number, head->ch[i]->pl_size);
		ft_printf("\"%s\" (\"%s\")!{eoc}\n", head->ch[i]->name, head->ch[i]->comment);
		i++;
	}
}

t_arena 	*fill_arena(t_arena *vm, int players, int x)
{
	int 	count;
	int 	a;
	int 	i;
	int 	index;

	count = 1;
	index = 0;
	while (count <= players)
	{
		a = index;
		i = 0;
		while (i < vm->ch[x]->pl_size)
		{
			vm->map[a] = vm->ch[x]->code[i];
			vm->color[a] = vm->ch[x]->number;
			i++;
			a++;
		}
		count++;
		index += MEM_SIZE / players;
		x++;
	}
	return (vm);
}

t_arena		*get_slider(t_arena *vm)
{
	int 	i;
	int 	place;
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

t_arena		*ready_to_start(t_arena *vm)
{
	int 	i;
	t_champion	*last;

	if (vm->print_type == 0) //устанавливаем для печати размер строки по умолчанию, если не было флага
		vm->print_type = 1;
	last = vm->champion; // нужен для заполнения массива
	i = 0;
	while (i < vm->players)
	{
		vm->ch[last->number - 1] = last;
		last = last->next;
		i++;
	}
	if (!vm->visual)
		inroduction(vm, vm->players); //представляем участников
	vm = fill_arena(vm, vm->players, 0); //записываем код в арену
	vm = get_slider(vm);
	return (vm);
}

int main(int argc, char **argv)
{
	t_arena		*vm;

	vm = init_arena();
	if (argc >= 2)
	{
		vm = check_input(argv, argc, vm); //проверяет валидность, заполняет структуру вм и чемпионов(лежат в вм) из файла
		vm = ready_to_start(vm);
		if (!vm->visual)
			start_war(vm);
		else
			show_war(vm);
	}
	else
//		usage(0); //как использовать если передать в функцию число 1 - запустит титульник
	free_arena(&vm); //очистка памяти
	return (0);
}