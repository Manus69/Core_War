#include "corewar.h"
//очистка памяти

void	free_slider(t_slider *slider, int count)
{
	t_slider *head;

	head = NULL;
	while (slider && count--)
	{
		if (slider->next)
			head = slider->next;
		free(slider);
		slider = head;
	}
	slider = NULL;
}

void	free_champions(t_champion *player, int count)
{
	t_champion	*head;

	head = NULL;
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
	int i;

	i = 0;
	while (i < 4)
	{
		if ((*arena) && (*arena)->ch[i])
			(*arena)->ch[i] = NULL;
		i++;
	}
	if ((*arena) && (*arena)->champion)
		free_champions((*arena)->champion, (*arena)->players);
	if ((*arena) && (*arena)->slider)
		free_slider((*arena)->slider, (*arena)->players);
	if (*arena)
		free(*arena);
	*arena = NULL;
}