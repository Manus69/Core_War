#include "corewar.h"

void	print_error(char *error, t_arena *vm) //генерация ошибок и чистка памяти
{
	perror(error);
	free_arena(&vm);
	exit(1);
}