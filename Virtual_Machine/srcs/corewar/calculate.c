#include "corewar.h"

int32_t		bytes_to_magic(const uint8_t *magic, size_t size)
{
	int32_t	result;
	int		sign;
	int		i;

	result = 0;
	sign = (magic[0] & 0x80);
	i = 0;
	while (size)
	{
		if (sign)
			result += ((magic[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += magic[size - 1] << (i++ * 8);
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
	return (bytes_to_magic(symbols, 4));
}