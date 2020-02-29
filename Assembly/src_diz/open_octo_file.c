//
// Created by Grass Emerald on 29/02/2020.
//

#include "asm.h"

int     read_my_binary(char *str, char **buf)
{
	int fd;
	size_t file_len;

	file_len = 0;
	if ((fd = open(str, O_RDONLY)) < 0)
		return (err_out("ERROR : FILE DOES NOT EXIST"));
	(*buf) = ft_binary_read(fd, &file_len);
	if (!(*buf) || file_len == 0)
		return (err_out("ERROR : CAN'T READ"));
	return (file_len);
}