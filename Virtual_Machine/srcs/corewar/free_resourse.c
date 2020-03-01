#include "corewar.h"
//очистка памяти
void	free_champions(t_champion *player)
{
	t_champion	*head;

	while (player)
	{
		if (player->name)
			ft_strdel(&(player->name));
		if (player->comment)
			ft_strdel(&(player->comment));
		if (player->code)
		{
			free(player->code);
			player->code = NULL;
		}
		head = player->next;
		free(player);
		player = head;
	}
	player= NULL;
}

void	free_arena(t_arena **arena)
{
	if ((*arena)->last_alive)
		free((*arena)->last_alive);
	if ((*arena)->champion)
		free_champions((*arena)->champion);
	if (*arena)
		free(*arena);
	*arena = NULL;
}