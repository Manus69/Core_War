/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 00:57:33 by selly             #+#    #+#             */
/*   Updated: 2020/07/01 15:56:37 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int				check_player_id(t_arena *vm, int type)
{
	t_champ	*buf;

	buf = NULL;
	if ((vm->players == 0 || vm->read_num == 0) && type)
		return (1);
	else if ((buf = vm->champion) != NULL && vm->read_num > 0)
	{
		while (buf != NULL)
		{
			if (vm->read_num == buf->num && type)
				print_error(DUPLICATE_ID_ERROR, vm);
			else if (vm->read_num == buf->num)
				return (0);
			buf = buf->next;
		}
	}
	return (1);
}

t_arena			*new_player(t_champ *player, t_arena *vm)
{
	if (vm->players > 0)
	{
		player->next = vm->champion;
		vm->champion = player;
	}
	else
		vm->champion = player;
	vm->players += 1;
	return (vm);
}

char			*read_str(int fd, int len, t_arena *vm)
{
	int			size;
	char		*name;

	if (!(name = ft_strnew(len)))
		print_error(MALLOC_ERROR, vm);
	size = read(fd, name, len);
	if (size < len)
		print_error(READ_ERROR, vm);
	return (name);
}

uint8_t			*read_code(int fd, size_t len, t_arena *vm)
{
	size_t		size;
	uint8_t		*code;

	if (!(code = (unsigned char *)malloc(sizeof(unsigned char) * len)))
		print_error(MALLOC_ERROR, vm);
	size = read(fd, code, len);
	if (size != len)
		print_error(CODE_SIZE_ERROR, vm);
	return (code);
}

t_arena			*get_champion(char *argv, t_arena *vm)
{
	int			fd;

	check_player_id(vm, 1);
	if ((fd = open(argv, O_RDONLY)) < 0)
		print_error(READ_ERROR, vm);
	if (get_magic(fd, vm) != COREWAR_EXEC_MAGIC)
		print_error(NONE_BIN_ERROR, vm);
	if (vm->players <= 3 && vm->read_num <= 4)
		vm = new_player(init_player(vm->read_num, vm), vm);
	else
		print_error(PLAYER_ERROR, vm);
	vm->champion->name = read_str(fd, PROG_NAME_LENGTH, vm);
	if (get_magic(fd, vm) != 0)
		print_error(NO_NULL_ERROR, vm);
	if ((vm->champion->size = get_magic(fd, vm)) < 0 ||
		vm->champion->size > CHAMP_MAX_SIZE)
		print_err_size(argv, vm);
	vm->champion->comment = read_str(fd, COMMENT_LENGTH, vm);
	if (get_magic(fd, vm) != 0)
		print_error(NO_NULL_ERROR, vm);
	vm->champion->code = read_code(fd, (size_t)(vm->champion->size), vm);
	close(fd);
	vm->read_arg = 0;
	vm->read_num = 0;
	return (vm);
}
