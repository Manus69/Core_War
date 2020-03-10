#include "corewar.h"

int 		check_args(uint8_t code, t_operation *op)
{
	int i;

	i = 0;
	while (i < 9)
	{
		if (code == op->args_code[i])
			return (1);
		i++;
	}
	return (0);
}

unsigned int	find_op(t_operation *op)
{
	uint8_t c;

	c = op->code;
	if (op->args_num == 1)
	{
		if (c == 0x01 || c == 0x09 || c == 0x0c || c == 0x0f)
			return (1);
	}
	return (0);
}

t_slider	*write_args_types(t_slider *s, t_operation *op, uint8_t code)
{
	int 			args_code;
	unsigned int	num;
	int 			type;

	if (op->read_args)
	{
		if (check_args(code, op)) {
			if (!(args_code = args_type_1(code, op->args_num))) //проверяем код аргументов
				return (s);
			num = op->args_num;
			while (num) {
				type = args_code % 10;
				s->type_of_args[num - 1] = type;
				args_code /= 10;
				num--;
			}
			s->step += 1;
			s->write = 1;
		}
	}
	else
		{
		if ((s->type_of_args[0] = find_op(op)) == 1)
			s->write = 1;
	}
	return (s);
}


uint32_t	move(t_slider *cursor, t_operation *op, t_arena *vm)
{
	unsigned int		i;
	uint32_t			step;

	i = 0;
	step = 0;
	step += 1 + (op->read_args ? 1 : 0); // перепрыгиваем код операции и аргумент если есть
	if (cursor->code >= 0x01 && cursor->code <= 0x10)
	{
		while (i < operation_list[cursor->code - 1].args_num)
		{
			step += next_step(cursor->type_of_args[i], op);
			if (vm->cycles == 6870)
				ft_printf("ok15 %d\n", i);
			i++;
		}
	}
	return (step);
}

int	is_register(t_arena *vm, int32_t place, int32_t step)
{
	int8_t r_id;

	r_id = read_byte(vm, place, step);
	return (r_id >= 1 && r_id <= REG_NUMBER);
}

int			is_args_valid(t_slider *cursor, t_arena *vm, t_operation *op) // nope
{
	unsigned int		i;
	uint32_t	step;

	i = 0;
	step = (1 + (op->read_args ? 1 : 0));
	while (i < op->args_num)
	{
		if ((cursor->type_of_args[i] == 3)
			&& !is_register(vm, cursor->place, step))
			return (0);
		step += next_step(cursor->type_of_args[i], op);
		i++;
	}
	return (1);
}

void	read_args_size(t_arena *vm, t_slider *s, t_operation *op)
{
	uint8_t byte; //int8_t

	byte = 0;
	if (op->read_args)
		byte = read_byte(vm, s->place, 1); // считываем размер args
		s = write_args_types(s, op, byte); // если байты в порядке и мы записали агрументы, тогда s->write == 1
		if (s->write && is_args_valid(s, vm, op))
		{
			s->step += 1;
			op->operation(vm, s); // запускаем функцию
			s->write = 0;
		}
		else
			s->step += move(s, op, vm);
}