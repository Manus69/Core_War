#include "corewar.h"

void		live(t_arena *vm, t_slider *s)
{
	int32_t		player_id;
	t_operation		*op;
	t_champion	*champ;

	op = &operation_list[s->code - 1];
	player_id = read_mem(vm, s, 1, op);
	vm->lives++;
	s->last_live = vm->cycles;
	champ = NULL;
	if (player_id <= -1 && player_id >= -((int32_t)vm->players))
	{
		champ = vm->ch[(player_id < 0 ? -player_id : player_id) - 1];
		champ->last_live = vm->cycles;
		champ->live++;
		vm->last_alive = champ;
	}
}

void		ld(t_arena *vm, t_slider *sl)
{
	int32_t			value;
	t_operation		*op;
	int 			ind;

	sl->step += 1;
	op = &operation_list[sl->code - 1];
	value = read_mem(vm, sl, 1, op);
	sl->carry = value == 0 ? 1 : 0;
	ind = read_byte(vm, sl->place, sl->step);
	sl->r[ind - 1] = value;
	sl->step += REG_NAME_SIZE;
}

void		st(t_arena *vm, t_slider *sl)
{
	int32_t	reg;
	int32_t	r_value;
	int32_t	place;

	sl->step += 1;
	reg = read_byte(vm, sl->place, sl->step);
	r_value = sl->r[reg - 1];
	sl->step += REG_NAME_SIZE;
	if (sl->type_of_args[1] == 3)
	{
		sl->r[(read_byte(vm, sl->place, sl->step)) - 1] = r_value;
		sl->step += REG_NAME_SIZE;
	}
	else
	{
		place = bytes_to_magic(vm->map,
							   sl->place + sl->step, IND_SIZE);
		magic_to_byte(vm->map, sl->place + (place % IDX_MOD),
					  r_value, DIR_SIZE);
		put_color(vm->color, sl->place + (place % IDX_MOD), sl, DIR_SIZE);
		sl->step += IND_SIZE;
	}
}

void		add(t_arena *vm, t_slider *sl)
{
	int32_t	reg1;
	int32_t	reg2;
	int32_t	reg3;
	int32_t	value;

	sl->step += 1;
	reg1 = read_byte(vm, sl->place, sl->step);
	sl->step += REG_NAME_SIZE;
	reg2 = read_byte(vm, sl->place, sl->step);
	sl->step += REG_NAME_SIZE;
	value = sl->r[reg1 - 1] + sl->r[reg2 - 1];
	sl->carry = value == 0 ? 1 : 0;
	reg3 = read_byte(vm, sl->place, sl->step);
	sl->r[reg3 - 1] = value;
	sl->step += REG_NAME_SIZE;
}