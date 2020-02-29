//
// Created by Grass Emerald on 29/02/2020.
//

#include "asm.h"

int     to_translate(char *str)
{
	if (!ft_match(str, "*.s", '*'))
		return (MISS_MATCH);
	else
		return (SUCCESS);
}

int     to_dizasm(char *str)
{
	if (!ft_match(str, "*.cor", '*'))
		return (MISS_MATCH);
	else
		return (SUCCESS);
}

int     take_name(int ac, char **av)
{
	if (ac < 2)
		return (ERR_USAGE);
	if (to_translate(av[1]))
		return (TO_TRANSLATE);
	else if (to_dizasm(av[1]))
		return (TO_DIZASM);
	else
		return (ERR_USAGE);
}