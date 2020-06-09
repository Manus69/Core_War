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

int			err_out(char *str, t_flag *has_flag)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	has_flag = free_structure(has_flag);
	return (0);
}

int			err_usage(char *str, t_flag *has_flag)
{
	if (str)
		ft_putstr_fd("ERROR : INCORRECT FILE_NAME\n", 2);
	else
	{
		ft_putstr("usage :\n\t\t./asm [-a | -n new_file_name] ");
		ft_putstr("%filename.s% or %filename.cor%\n");
	}
	has_flag = free_structure(has_flag);
	return (0);
}

void		init_functions(int (*actions[])(char *, t_flag *), t_flag *flag)
{
	actions[0] = &err_out;
	actions[1] = &asm_s;
	actions[2] = &dizasm;
	actions[3] = &err_usage;
	(*flag).flag_a = 0; 			//есть ли флаг -а
	(*flag).visible = 0;			//?
	(*flag).change_name = 0; 		//есть ли флаг смены имени файла
	flag->file_name = NULL;			//старое имя. Всегда можно использовать
	flag->new_file_name = NULL;		//новое имя если есть
}

int			main(int ac, char **av)
{
	t_flag	has_flag; 					//структура для работы с флагом
	int		arg_count; 				//для отслеживания кол-ва аргументов
	int	 	(*actions[4])(char *, t_flag *);

	arg_count = 1;
	init_functions(actions, &has_flag); 	// + инициализация значений для структуры флага
	actions[take_name(ac, av, &arg_count, &has_flag)](av[arg_count], &has_flag);
	return (0);
}
