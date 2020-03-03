#include "corewar.h"

int 		check_player_id(t_arena *vm, int type) //проверяем уникальность номера игрока
{
	t_champion	*buf;
	if ((vm->players == 0 || vm->read_num == 0) && type)
		return (1);
	else if ((buf = vm->champion) != NULL && vm->read_num > 0)
	{
		while (buf != NULL)
		{
			if (vm->read_num == buf->number && type)
				print_error(DUPLICATE_ID_ERROR, vm);
			else if (vm->read_num == buf->number)
				return (0);
			buf = buf->next;
		}
	}
	return (1);
}

t_arena		*new_player(t_champion	*player, t_arena *vm) //добавляем нового игрока
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

char		*read_str(int fd, int len, t_arena *vm) //читаем строку из памяти
{
	int		size;
	char	*name;

	if (!(name = ft_strnew(len)))
		print_error(MALLOC_ERROR, vm);
	size = read(fd, name, len);
	if (size < len)
		print_error(READ_ERROR, vm);
	return (name);
}

uint8_t		*read_code(int fd, size_t len, t_arena *vm) //читаем код
{
	size_t	size;
	uint8_t	*code;
	char last;

	if (!(code = (unsigned char *)malloc(sizeof(unsigned char) * len)))
		print_error(MALLOC_ERROR, vm);
	size = read(fd, code, len); //читаем код
	read(fd, &last, 1);
	if (last != 0) //проверяем что считан весь файл
		print_error(CODE_SIZE_ERROR, vm);
	if (size != len ) //если размер кода больше, чем описано значит ошибка
		print_error(CODE_SIZE_ERROR, vm);
	return (code);
}

t_arena		*get_champion(char 	*argv, t_arena *vm) //открываем файл. проверяем на валидность, считываем инфу, закрываем
{
	int			fd;

	check_player_id(vm, 1);//проверяем не дублируется ли введеный номер игрока
	if ((fd = open(argv, O_RDONLY)) < 0)//открываем
		print_error(READ_ERROR, vm);
	if (get_magic(fd, vm) != COREWAR_EXEC_MAGIC)//проверяем, что файл бинарный
		print_error(NONE_BIN_ERROR, vm);
	if (vm->players <= 3 && vm->read_num <= 4)//проверяем чобы игроков было не большк 4х
		vm = new_player(init_player(vm->read_num, vm), vm);
	else
		print_error(PLAYER_ERROR, vm);
	vm->champion->name = read_str(fd, PROG_NAME_LENGTH, vm); //читаем имя и записываем в строку
	if (get_magic(fd, vm) != 0) //проверяем на месте ли нулевой разделитель
		print_error(NO_NULL_ERROR, vm);
	if ((vm->champion->pl_size = get_magic(fd, vm)) < 0 //считываем размер кода
		|| vm->champion->pl_size > CHAMP_MAX_SIZE)
		print_error(SIZE_ERROR, vm);
	vm->champion->comment = read_str(fd, COMMENT_LENGTH, vm); //читаем комментарий игрока и записываем в строку
	vm->champion->code = read_code(fd, (size_t)(vm->champion->pl_size), vm); //читаем и записыаваем испоняемый код игрока
	close(fd); //закрываем
	vm->read_arg = 0; // чистим флаги
	vm->read_num = 0;
	return (vm);
}