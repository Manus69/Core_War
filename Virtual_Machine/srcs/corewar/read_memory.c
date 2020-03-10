#include "corewar.h"

uint32_t	next_step(uint8_t arg_type, t_operation *op)
{
	if (arg_type == 1)
		return (op->size_t_dir);
	else if (arg_type == 2)
		return (IND_SIZE);
	else if (arg_type == 3)
		return (REG_NAME_SIZE);
	return (0);
}

int32_t		read_mem(t_arena *vm, t_slider *s, uint8_t i, t_operation *op)
{
	int32_t		read;
	int32_t		place;

	read = 0;
	if (s->type_of_args[i - 1] == 1) //if T_DIR
		read = bytes_to_magic(vm->map, s->place + s->step, op->size_t_dir);
	else if (s->type_of_args[i - 1] == 2) //if T_INDIR
	{
		place = bytes_to_magic(vm->map, s->place + s->step, IND_SIZE);
		place = op->mod ? (place % IDX_MOD) : place;
		read = bytes_to_magic(vm->map, s->place + place, DIR_SIZE);
	}
	else if (s->type_of_args[i - 1] == 3) //if T_REG
		read = s->r[read_byte(vm, s->place, s->step) - 1];
	s->step += next_step(s->type_of_args[i - 1], op);
	return (read);
}