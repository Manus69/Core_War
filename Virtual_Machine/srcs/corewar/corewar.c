#include "corewar.h"

void	inroduction(t_arena *vm)
{
	int 		count;
	t_champion	*head;

	count = vm->players;
	head = vm->champion;
	ft_printf("{green}Introducing contestants...{eoc}\n");
	while (count && head)
	{
		if (count == 1)
			ft_printf("{red}* :smile_8  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
		else if (count == 2)
			ft_printf("{red}* :smile_7  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
		else if (count == 3)
			ft_printf("{red}* :smile_5  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
		else if (count == 4)
			ft_printf("{red}* :smile_1  Player %d: {blue}weighing %d bytes, ", head->number, head->pl_size);
		ft_printf("\"%s\" (\"%s\")!{eoc}\n", head->name, head->comment);
		head = head->next;
		count--;
	}
}

void	ready_to_start(t_arena *vm)
{
	inroduction(vm);
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
	free_arena(&vm); //очистка памяти
	return (0);
}