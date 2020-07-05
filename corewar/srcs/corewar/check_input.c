/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:43:03 by selly             #+#    #+#             */
/*   Updated: 2020/07/03 17:51:06 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_file_name(char *name, char *str)
{
	while (*name && !(*name == '.' && *(name + 1) == 'c'))
		name++;
	while (*name && *str)
	{
		if (*name != *str)
			break ;
		name++;
		str++;
	}
	if (*name == *str)
		return (1);
	else
		return (0);
}

int			check_name(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break ;
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	else
		return (0);
}

t_arena		*find_num_arg(char *argv, t_arena *vm)
{
	long	num;

	if ((num = ft_atoi_size_t(argv)) < 0)
		print_error(ARGS_ERROR, vm);
	if (vm->read_arg == 3)
	{
		if (num >= 1 && num <= 4)
			vm->read_num = (int)num;
		else
			print_error(PLAYER_ID_ERROR, vm);
	}
	else if (vm->read_arg == 2)
		vm->show = (size_t)num;
	else if (vm->read_arg == 1)
		vm->d_dump = (size_t)num;
	else
		print_error(ARGS_ERROR, vm);
	vm->read_arg = vm->read_arg == 3 ? -1 : -2;
	return (vm);
}

t_arena		*find_flag(char *argv, t_arena *vm)
{
	int		len;

	len = ft_strlen(++argv);
	if (len == 1 && *argv == 'd' && vm->print_type == 0 && (vm->read_arg = 1))
		vm->print_type = 1;
	else if (len == 1 && *argv == 'a' && vm->aff_print == 0)
		vm->aff_print = 1;
	else if (len == 1 && *argv == 'c' && vm->nice == 0)
		vm->nice = 1;
	else if (len == 1 && *argv == 'v' && vm->visual == 0)
		vm->visual = 1;
	else if (len == 1 && *argv == 's' && vm->show == 0 && (vm->read_arg = 2))
		vm->show = 1;
	else if (len == 1 && *argv == 'n' &&
	vm->read_num == 0 && (vm->read_arg = 3))
		vm->read_num = 1;
	else if (len == 4 && check_name(argv, "dump") &&
		vm->print_type == 0 && (vm->read_arg = 1))
		vm->print_type = 2;
	else
	{
		usage(0, vm->nice);
		print_error(FLAG_ERROR, vm);
	}
	return (vm);
}

t_arena		*check_input(char **argv, int argc, t_arena *vm)
{
	argv++;
	while (argc--)
	{
		if (vm->read_arg > 0)
			vm = find_num_arg(*argv, vm);
		else if (**argv == '-')
			vm = find_flag(*argv, vm);
		else if (check_file_name(*argv, ".cor"))
			vm = get_champion(*argv, vm);
		else
		{
			usage(0, vm->nice);
			print_error(FLAG_ERROR, vm);
		}
		argv++;
	}
	if (vm->read_arg || vm->read_arg < 0 ||
	((vm->nice || vm->aff_print || vm->visual) && vm->players <= 0))
	{
		usage(0, vm->nice);
		print_error(ARGS_ERROR, vm);
	}
	else
		vm = set_player_id(vm);
	return (vm);
}
