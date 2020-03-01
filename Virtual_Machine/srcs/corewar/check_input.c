#include "corewar.h"

int 	check_file_name(char  *name, char *str) // проверка корректности имени файла
{
	while (*name && *name != '.')
		name++;
	while (*name && *str)
	{
		if (*name != *str)
			break;
		name++;
		str++;
	}
	if (*name == *str)
		return (1);
	else
		return (0);
}

int 	check_name(char *s1, char *s2) //проверка того, что строки равны
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	else
		return (0);
}

t_arena		*find_num_arg(char 	*argv,t_arena *vm) // ищет число и записывает его инфу в зависимости от флага
{
	long num;

	if ((num = ft_atoi_size_t(argv)) < 0) //определяет размер числа (циклов может быть больше чем вместит инт)
		print_error(ARGS_ERROR, vm);
	if (vm->read_arg == 3)  //если нужно изменить номер игрока флаг -n
	{
		if (num >= 1 && num <= 4) //номер может быть от 1го до 4х
			vm->read_num = (int)num; //next player num
		else
			print_error(PLAYER_ID_ERROR, vm);
	}
	else if (vm->read_arg == 2) //после какого числа циклов отразить состояние памяти флаг -s
		vm->show = (size_t)num; //num cycles to show
	else if (vm->read_arg == 1) //после какого числа циклов отразить состояние памяти и закончить игру флаги -d и -dump
		vm->d_dump = (size_t)num;
	else
		print_error(ARGS_ERROR, vm);
	vm->read_arg = vm->read_arg == 3 ? -1 : -2; //был ли флаг n (-1) или другой флаг (-2)?
	return (vm);
}

t_arena		*find_flag(char *argv, t_arena *vm) //ищет и определяет тип флага
{
	int 	len;

	argv++;
	len = ft_strlen(argv);
	if (len == 1 && *argv == 'd' && vm->print_type == 0 && (vm->read_arg = 1))
		vm->print_type = 1; //64 bytes per_line
	else if (len == 1 && *argv == 'a' && vm->aff_print == 0)
		vm->aff_print = 1; //for aff
	else if (len == 1 && *argv == 'v' && vm->visual == 0)
		vm->visual = 1; //for visual
	else if (len == 1 && *argv == 's' && vm->show == 0 && (vm->read_arg = 2))
		vm->show = 1; //for show
	else if (len == 1 && *argv == 'n' && vm->read_num == 0 && (vm->read_arg = 3))
		vm->read_num = 1; //for num of player
	else if (len == 4 && check_name(argv, "dump") &&
		vm->print_type == 0 && (vm->read_arg = 1))
		vm->print_type = 2;  //32 bytes per_line
	else
	{
		usage(0);
		print_error(FLAG_ERROR, vm);
	}
	return (vm);
}

t_arena 	*check_input(char **argv, int argc, t_arena *vm) //проверка и считывание всего ввода
{
	argc--;
	argv++;
	while (argc--)
	{
		if (vm->read_arg > 0) //запускается если ранее были флаги после которых должно идти число
			vm = find_num_arg(*argv, vm); //проверяет наличие числа и считывает его
		else if (**argv == '-') //проверка на флаги
			vm = find_flag(*argv, vm);//проверяет знакомые флаги, если флаг неизвестен будет ошибка
		else if (check_file_name(*argv, ".cor")) //проверяет название файла
			vm = get_champion(*argv, vm);//проверяет файл и читает игрока
		else //если введен не флаг и не файл игрока то будет ошибка и юзедж
		{
			usage(0);
			print_error(FLAG_ERROR, vm);
		}
		argv++;
	}
	if (vm->read_arg || vm->read_arg < 0)//если не введен флаг игрока но есть флаги будет ошибка
	{
		usage(0);
		print_error(ARGS_ERROR, vm);
	}
	return (vm);
}