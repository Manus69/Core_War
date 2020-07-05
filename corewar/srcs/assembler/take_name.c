/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:22:53 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 18:00:00 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		to_translate(char *str)
{
	if (!ft_match(str, "*.s", '*'))
		return (MISS_MATCH);
	else
		return (SUCCESS);
}

int		to_dizasm(char *str)
{
	if (!ft_match(str, "*.cor", '*'))
		return (MISS_MATCH);
	else
		return (SUCCESS);
}

int		take_name(int ac, char **av, int *argnum, t_flag *check)
{
	if (ac < 2)
		return (ERR_USAGE);
	else if (!ft_strcmp("-n", av[1]) && ac < 4)
		return (ERR_USAGE);
	if (ac > 2 && av[1][0] == '-' && is_flag(av[*argnum], check, argnum, av))
		*argnum += 1;
	if (to_translate(av[*argnum]))
		return (TO_TRANSLATE);
	else if (to_dizasm(av[*argnum]))
		return (TO_DIZASM);
	else
		return (ERR_USAGE);
}
