/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:21:32 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:22:10 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		err_out(char *str, t_flags *has_flag)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	has_flag = free_structure(has_flag);
	return (0);
}

int		err_usage(char *str, t_flags *has_flag)
{
	if (str)
		ft_putstr_fd("ERROR : INCORRECT FILE_NAME\n", 2);
	else
		ft_putstr("usage :\n\t\t./asm %filename.s% or %filename.cor%\n");
	has_flag = free_structure(has_flag);
	return (0);
}

void	init_functions(int (*actions[])(char *,  t_flags *), t_flags *has_flag)
{
	actions[0] = &err_out;
	actions[1] = &asm_s;
	actions[2] = &dizasm;
	actions[3] = &err_usage;

	(*has_flag).flag_a = 0;
	(*has_flag).change_name = 0;
	has_flag->file_name = NULL;
	has_flag->new_file_name = NULL;
}

int		main(int ac, char **av)
{
	t_flags	has_flag;
	int		arg_count;
	int		(*actions[4])(char *, t_flags *);

	arg_count = 1;
	init_functions(actions, &has_flag);
	actions[take_name(ac, av, &arg_count, &has_flag)](av[arg_count], &has_flag);
	return (0);
}
