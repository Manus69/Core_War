//
// Created by Grass Emerald on 29/02/2020.
//

#include "asm.h"

int     err_out(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

int    err_usage(char *str)
{
	if (str)
		ft_putstr_fd("ERROR : INCORRECT FILE_NAME\n", 2);
	else
		ft_putstr("usage :\n\t\t./asm %filename.s% or %filename.cor%\n");
	return (0);
}

void     init_functions(int (*actions[])(char *))
{
	actions[0] = &err_out;
	actions[1] = &asm_s;
	actions[2] = &dizasm;
	actions[3] = &err_usage;
}

int     main(int ac, char **av)
{
	int (*actions[4])(char *);
	init_functions(actions);
	actions[take_name(ac, av)](av[1]);
	return (0);
}