//
// Created by Grass Emerald on 29/02/2020.
//

#include "asm.h"

int     err_validate(t_dsm *src_code)
{
	free(src_code->input);
	ft_putstr_fd("ERROR : *.cor ARE BAD\n", 2);
	return (0);
}

int     validate_binary(t_dsm *src_code)
{
	int chanse;

	if (src_code->file_len < 4)
		return (err_validate(src_code));
	chanse = ((int)src_code->input);
	if (((unsigned int)src_code->input) != COREWAR_EXEC_MAGIC)
		return (err_validate(src_code));
}

int     read_my_binary(char *str, char **buf)
{
	int fd;
	size_t file_len;

	file_len = 0;
	if ((fd = open(str, O_RDONLY)) < 0)
		return (err_out("ERROR : FILE DOES NOT EXIST"));
	(*buf) = ft_binary_read(fd, &file_len);
	close(fd);
	if (!(*buf) || file_len == 0)
		return (err_out("ERROR : CAN'T READ"));
	return (file_len);
}