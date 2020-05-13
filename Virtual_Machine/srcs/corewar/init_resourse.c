#include "corewar.h"

t_slider	*init_slider(t_arena *vm, int	id, int place, int flag)
{
	t_slider	*new;
	static uint32_t	cursor_id;

	if (!(new = (t_slider *)ft_memalloc(sizeof(t_slider))))
		print_error(MALLOC_ERROR, vm);
	new->id = ++cursor_id;
	new->carry = 0;
	new->code = 0;
	new->last_live = 0;
	new->cool_down = 0;
	new->place = place;
	new->step = 0;
	if (flag)
	{
		new->r[0] = -(vm->ch[id]->number);
		new->player = vm->ch[id];
	}
	return (new);
}

t_arena		*set_player_id(t_arena *vm)
{
	int 	count;
	t_champion	*head;

	head = vm->champion;
	count = vm->players;
	while (count && head)
	{
		vm->read_num = count;
		if (head->number == 0 && check_player_id(vm, 0))
		{
			head->number = count;
			head = head->next;
		}
		else if (head->number != 0 )
		{
			head = head->next;
			continue;
		}
		count--;
	}
	vm->last_alive = vm->champion;
	return (vm);
}

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
	buffer->nice = 0;
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
	buffer->viz = NULL;
	return (buffer);
}