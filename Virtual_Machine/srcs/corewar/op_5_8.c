#include "corewar.h"

void		sub(t_arena *vm, t_slider *sl)
{
	int32_t	reg1;
	int32_t	reg2;
	int32_t	reg3;
	int32_t	value;

	reg1 = read_byte(vm, sl->place, sl->step);
	sl->step += REG_NAME_SIZE;
	reg2 = read_byte(vm, sl->place, sl->step);
	sl->step += REG_NAME_SIZE;
	value = sl->r[reg1 - 1] - sl->r[reg2 - 1];
	sl->carry = value == 0 ? 1 : 0;
	reg3 = read_byte(vm, sl->place, sl->step);
	sl->r[reg3 - 1] = value;
	sl->step += REG_NAME_SIZE;
}

void		and(t_arena *vm, t_slider *sl)
{
	int32_t	value_1;
	int32_t	value_2;
	int32_t	value;
	int32_t	r_id;

	value_1 = read_mem(vm, sl, 1, &operation_list[sl->code - 1]);
	value_2 = read_mem(vm, sl, 2, &operation_list[sl->code - 1]);
	value = value_1 & value_2;
	sl->carry = value == 0 ? 1 : 0;
	r_id = read_byte(vm, sl->place, sl->step);
	sl->r[r_id - 1] = value;
	sl->step += REG_NAME_SIZE;
}

void		or(t_arena *vm, t_slider *sl)
{
	int32_t	value_1;
	int32_t	value_2;
	int32_t	value;
	int32_t	r_id;

	value_1 = read_mem(vm, sl, 1, &operation_list[sl->code - 1]);
	value_2 = read_mem(vm, sl, 2, &operation_list[sl->code - 1]);
	value = value_1 | value_2;
	sl->carry = value == 0 ? 1 : 0;
	r_id = read_byte(vm, sl->place, sl->step);
	sl->r[r_id - 1] = value;
	sl->step += REG_NAME_SIZE;
}

void		xor(t_arena *vm, t_slider *sl)
{
	int32_t	value_1;
	int32_t	value_2;
	int32_t	value;
	int32_t	r_id;

	value_1 = read_mem(vm, sl, 1, &operation_list[sl->code - 1]);
	value_2 = read_mem(vm, sl, 2, &operation_list[sl->code - 1]);
	value = value_1 ^ value_2;
	sl->carry = value == 0 ? 1 : 0;
	r_id = read_byte(vm, sl->place, sl->step);
	sl->r[r_id - 1] = value;
	sl->step += REG_NAME_SIZE;
}