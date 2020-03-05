#include "corewar.h"
//очистка памяти
void	free_champions(t_champion *player, int count)
{
	t_champion	*head;

	head = 0;
	while (player && count--)
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
		if (player->next)
			head = player->next;
		free(player);
		player = head;
	}
	player= NULL;
}

void	free_arena(t_arena **arena)
{
	if ((*arena)->champion)
		free_champions((*arena)->champion, (*arena)->players);
	if (*arena)
		free(*arena);
	*arena = NULL;
}