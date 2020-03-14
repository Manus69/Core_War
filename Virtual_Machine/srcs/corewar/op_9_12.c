#include "corewar.h"

void		zjmp(t_arena *vm, t_slider *sl)
{
	int32_t addr;

	addr = read_mem(vm, sl, 1, &operation_list[sl->code - 1]);
	if (sl->carry)
	{
		sl->place = find_place(sl->place + (addr % IDX_MOD));
		sl->step = 0;
	}
}

void		ldi(t_arena *vm, t_slider *sl)
{
	int32_t	addr1;
	int32_t	addr2;
	int32_t	reg;

	sl->step += 1;
	addr1 = read_mem(vm, sl, 1, &operation_list[sl->code - 1]);
	addr2 = read_mem(vm, sl, 2, &operation_list[sl->code - 1]);
	reg = read_byte(vm, sl->place, sl->step);
	sl->r[reg - 1] = bytes_to_magic(vm->map, (sl->place + ((addr1 + addr2) % IDX_MOD)), DIR_SIZE);
	sl->step += REG_NAME_SIZE;
}

void		sti(t_arena *vm, t_slider *sl)
{
	int32_t	value;
	int32_t	addr_1;
	int32_t	addr_2;

	sl->step += 1;
	value = sl->r[read_byte(vm, sl->place, sl->step) - 1];
	sl->step += REG_NAME_SIZE;
	addr_1 = read_mem(vm, sl, 2, &operation_list[sl->code - 1]);
	addr_2 = read_mem(vm, sl, 3, &operation_list[sl->code - 1]);
	magic_to_byte(vm->map,(sl->place + ((addr_1 + addr_2) % IDX_MOD)), value, DIR_SIZE);
	put_color(vm->color,(sl->place + ((addr_1 + addr_2) % IDX_MOD)), sl, DIR_SIZE);
}

void		fork_op(t_arena *vm, t_slider *sl)
{
	int32_t		addr;
	t_slider	*new;

	addr = read_mem(vm, sl, 1, &operation_list[sl->code - 1]);
	if ((new = copy_slider(vm, sl, addr % IDX_MOD)))
		new->next = vm->slider;
	vm->slider = new;
	vm->num_slider++;
}