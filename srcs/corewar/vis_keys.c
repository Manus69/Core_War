/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 20:51:15 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 21:19:32 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		update_map(t_arena *vm, t_slider *sl, int32_t pl, int32_t size)
{
	int32_t value;

	value = ((sl->player->num - 1) % 4) + 1;
	while (size)
	{
		vm->viz->map[find_place(pl + size - 1)].i = value;
		vm->viz->map[find_place(pl + size - 1)].wait_store = 50;
		size--;
	}
}

void		clear_slider(t_arena *vm, t_slider *sl)
{
	if (vm->viz->map[sl->place].i >= 5
		&& vm->viz->map[sl->place].i <= 5 + 4)
		vm->viz->map[sl->place].i = vm->viz->map[sl->place].i - 5;
}

void		set_key(t_arena *vm)
{
	if (vm->viz->key == ' ')
		vm->viz->go = !(vm->viz->go);
	else if (vm->viz->key == '1')
		vm->viz->speed += 10;
	else if (vm->viz->key == '2')
		vm->viz->speed += 100;
	else if (vm->viz->key == '3')
		vm->viz->speed -= 10;
	else if (vm->viz->key == '4')
		vm->viz->speed -= 100;
	else if (vm->viz->key == '5')
		vm->viz->speed = 30;
	vm->viz->go = (!vm->num_slider) ? 0 : vm->viz->go;
	vm->viz->speed = (vm->viz->speed < 1) ? 1 : vm->viz->speed;
	vm->viz->speed = (vm->viz->speed > 600) ? 600 : vm->viz->speed;
}
