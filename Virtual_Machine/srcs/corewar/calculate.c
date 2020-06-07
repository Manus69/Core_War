/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 01:13:57 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 09:29:31 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

uint32_t			step(t_slider *cursor, t_oper *op)
{
	unsigned int	i;
	uint32_t		step;

	i = 0;
	step = 0;
	step += 1 + (op->read_args ? 1 : 0);
	while (i < g_operation_list[cursor->code - 1].args_num)
	{
		step += next_step(cursor->type_of_args[i], op);
		i++;
	}
	return (step);
}

int32_t				find_place(int32_t place)
{
	place %= MEM_SIZE;
	if (place < 0)
		place += MEM_SIZE;
	return (place);
}

void				magic_to_byte(uint8_t *m, int32_t p, int32_t val, int32_t s)
{
	int8_t			i;

	i = 0;
	while (s)
	{
		m[find_place(p + s - 1)] = (uint8_t)((val >> i) & 0xFF);
		i += 8;
		s--;
	}
}

int32_t				bytes_to_magic(const uint8_t *m, int32_t place, size_t size)
{
	int32_t	result;
	int		sign;
	int		i;

	result = 0;
	sign = (m[find_place(place)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((m[find_place(place + size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += m[find_place(place + size - 1)] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

int32_t				get_magic(int fd, t_arena *vm)
{
	int				bytes;
	uint8_t			symbols[4];

	bytes = read(fd, &symbols, 4);
	if (bytes < 4)
		print_error(READ_ERROR, vm);
	return (bytes_to_magic(symbols, 0, 4));
}
