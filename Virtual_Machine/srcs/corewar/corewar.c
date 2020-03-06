#include "corewar.h"

void	inroduction(t_champion *head, int count)
{
	if (count == 0)
	{
		ft_printf("{green}Introducing contestants...{eoc}\n");
		return;
	}
	else
		inroduction(head->next, count - 1);
	if (count == 1)
		ft_printf("{red}* :smile_1  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
	else if (count == 2)
		ft_printf("{red}* :smile_7  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
	else if (count == 3)
		ft_printf("{red}* :smile_5  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
	else if (count == 4)
		ft_printf("{red}* :smile_8  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
	ft_printf("\"%s\" (\"%s\")!{eoc}\n", head->name, head->comment);
}

t_arena 	*fill_arena(t_arena *vm, t_champion *ch, int players)
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
		while (i < ch->pl_size)
		{
			vm->map[a] = ch->code[i];
			i++;
			a++;
		}
		count++;
		index += MEM_SIZE / players;
		ch = ch->next;
	}
	return (vm);
}

void	ready_to_start(t_arena *vm)
{
	if (vm->print_type == 0)
		vm->print_type = 1; //устанавливаем для печати размер строки по умолчанию, если не было флага
	inroduction(vm->champion, vm->players); //представляем участников
	vm = fill_arena(vm, vm->champion, vm->players); //записываем код в арену
	print_mem_status(vm); //печать состояния памяти
}

int main(int argc, char **argv)
{
	t_arena		*vm;

	vm = init_arena();
	if (argc >= 2)
	{
		vm = check_input(argv, argc, vm); //проверяет валидность, заполняет структуру вм и чемпионов(лежат в вм) из файла
		ready_to_start(vm);
	}
	else
		usage(0); //как использовать если передать в функцию число 1 - запустит титульник
	ft_printf(":smile_14 {red}Contesant %d,{Lblue} %s,{green} has won!{eoc} \n", vm->last_alive->number, vm->last_alive->name); //печать победителя
	free_arena(&vm); //очистка памяти
	return (0);
}