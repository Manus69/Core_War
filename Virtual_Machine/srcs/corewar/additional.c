# include "corewar.h"

int 	args_type_2(int8_t code)
{
	if (code == (int8_t)0x54)
		return (333);
	if (code == (int8_t)0xa4)
		return (113);
	if (code == (int8_t)0xb4)
		return (123);
	if (code == (int8_t)0x94)
		return (133);
	if (code == (int8_t)0xe4)
		return (213);
	if (code == (int8_t)0xf4)
		return (223);
	if (code == (int8_t)0xd4)
		return (233);
	if (code == (int8_t)0x64)
		return (313);
	if (code == (int8_t)0x68)
		return (311);
	if (code == (int8_t)0x78)
		return (321);
	if (code == (int8_t)0x58)
		return (311);
	return (0);
}

int 	args_type_1(int8_t code, unsigned int num)
{
	if (num == 1)
	{
		if (code == (int8_t)0x80)
			return (1);
		if (code == (int8_t)0x40)
			return (3);
	}
	else if (num == 2)
	{
		if (code == (int8_t)0x90)
			return (13);
		if (code == (int8_t)0xd0)
			return (23);
		if (code == (int8_t)0x50)
			return (33);
		if (code == (int8_t)0x70)
			return (32);
	}
	else if (num == 3)
		return (args_type_2(code));
	return (0);
}

int 	is_op(int8_t byte)
{
	return (byte >= 0x01 && byte <= 0x10);
}

int8_t 		read_byte(t_arena *vm, int32_t	place, int32_t step)
{
	int32_t 	index;
	uint8_t 		read;

	index = find_place(place + step);
	read = vm->map[index];
	return (read);
}

t_slider	*copy_slider(t_arena *vm, t_slider *sl, int32_t addr)
{
	t_slider	*new;
	int			i;

	addr = find_place(sl->place + addr);
	new = init_slider(vm, 0, addr, 0);
	i = 0;
	while (i < REG_NUMBER)
	{
		new->r[i] = sl->r[i];
		i++;
	}
	new->carry = sl->carry;
	new->last_live = sl->last_live;
	new->player = sl->player;
	return (new);
}

