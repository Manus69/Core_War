#include "corewar.h"

int main(int argc, char **argv)
{
	t_arena		*vm;

	vm = init_arena();
	if (argc >= 2)
		vm = check_input(argv, argc, vm); //проверяет валидность, заполняет структуру вм и чемпионов(лежат в вм) из файла
	else
		usage(0); //как использовать если передать в функцию число 1 - запустит титульник
	free_arena(&vm); //очистка памяти
	return (0);
}