/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:22:53 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:23:22 by gemerald         ###   ########.fr       */
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

int		take_name(int ac, char **av, int *arg_count, t_flags *has_flag)
{
	if (ac < 2)
		return (ERR_USAGE);
	if (ac > 2 && av[1][0] == '-' &&
	is_flag(av[*arg_count], has_flag, arg_count, av)) //проверяет флаги -a -n
		*arg_count += 1;
	if (to_translate(av[*arg_count]))
		return (TO_TRANSLATE);
	else if (to_dizasm(av[*arg_count]))
		return (TO_DIZASM);
	else
		return (ERR_USAGE);
}
