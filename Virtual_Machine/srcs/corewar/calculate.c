#include "corewar.h"

int32_t		find_place(int32_t place)
{
	place %= MEM_SIZE;
	if (place < 0)
		place += MEM_SIZE;
	return (place);
}


void		magic_to_byte(uint8_t *map, int32_t place, int32_t value, int32_t s)
{
	int8_t i;

	i = 0;
	while (s)
	{
		map[find_place(place + s - 1)] = (uint8_t)((value >> i) & 0xFF);
		i += 8;
		s--;
	}
}

int32_t		bytes_to_magic(const uint8_t *magic, int32_t place, size_t size)
{
	int32_t	result;
	int		sign;
	int		i;

	result = 0;
	sign = (magic[find_place(place)] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((magic[find_place(place + size - 1)] ^ 0xFF) << (i++ * 8));
		else
			result += magic[find_place(place + size - 1)] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	return (result);
}

int32_t		get_magic(int fd, t_arena *vm) //считывыет 4 части по 8 байт и возвращает 32 байта
{
	int	bytes;
	uint8_t	symbols[4];

	bytes = read(fd, &symbols, 4);
	if (bytes < 4)
		print_error(READ_ERROR, vm);
	return (bytes_to_magic(symbols,0, 4));
}