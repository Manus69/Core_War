#include "corewar.h"

t_champion	*init_player(int id, t_arena *vm)
{
	t_champion	*new;

	if (!(new = (t_champion *)ft_memalloc(sizeof(t_champion))))
		print_error(MALLOC_ERROR, vm);
	new->number = id;
	new->name = NULL;
	new->pl_size = 0;
	new->code = 0;
	new->comment = NULL;
	new->next = NULL;
	return (new);
}

t_arena		*init_arena(void)
{
	t_arena		*buffer;

	if (!(buffer = (t_arena *)ft_memalloc(sizeof(t_arena))))
		print_error(MALLOC_ERROR, buffer);
	buffer->read_arg = 0;
	buffer->players = 0;
	buffer->read_num = 0;
	buffer->cycles = 0;
	buffer->d_dump = 0;
	buffer->aff_print = 0;
	buffer->visual = 0;
	buffer->print_type = 0;
	buffer->death_coming = CYCLE_TO_DIE;
	buffer->last_alive = NULL;
	buffer->champion = NULL;
	return (buffer);
}