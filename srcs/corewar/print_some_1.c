/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_some_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 13:13:06 by selly             #+#    #+#             */
/*   Updated: 2020/07/03 17:53:23 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			print_err_size(char *file, t_arena *vm)
{
	ft_putstr_fd("\n\033[0;31mError: File ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(" has too large a code (", 2);
	ft_putnbr_fd(vm->champion->size, 2);
	ft_putstr_fd(" bytes > ", 2);
	ft_putnbr_fd(CHAMP_MAX_SIZE, 2);
	ft_putstr_fd(" bytes)\033[0m\n", 2);
	free_arena(&vm);
	exit(1);
}

void			print_error(char *error, t_arena *vm)
{
	ft_putstr_fd(error, 2);
	free_arena(&vm);
	exit(1);
}

void			color_output(int color, uint8_t value, int nice)
{
	if (nice)
	{
		if (color == 0)
			ft_printf("{Lblue}%.2x{eoc} ", value);
		else if (color == 1)
			ft_printf("{cyan}%.2x{eoc} ", value);
		else if (color == 2)
			ft_printf("{yellow}%.2x{eoc} ", value);
		else if (color == 3)
			ft_printf("{purple}%.2x{eoc} ", value);
		else if (color == 4)
			ft_printf("{red}%.2x{eoc} ", value);
	}
	else
		ft_printf("%.2x ", value);
}

void			put_color(int *color, int32_t place, t_slider *sl, int32_t s)
{
	int8_t	i;
	int32_t	addr;

	i = 0;
	while (s)
	{
		addr = find_place(place + s - 1);
		color[addr] = sl->player->num;
		i += 8;
		s--;
	}
}

void			print_mem_status(t_arena *vm)
{
	int		i;
	int		line;
	int		format;

	i = 0;
	line = 1;
	format = vm->print_type == 1 ? 64 : 32;
	while (i < MEM_SIZE)
	{
		if (line == 0 || line == 1)
		{
			if (vm->nice)
				ft_printf("{Lgray}%.4p :{eoc} ", i);
			else
				ft_printf("%.4p : ", i);
		}
		color_output(vm->color[i], vm->map[i], vm->nice);
		if (line == format)
		{
			ft_printf("\n");
			line = 0;
		}
		line++;
		i++;
	}
}
