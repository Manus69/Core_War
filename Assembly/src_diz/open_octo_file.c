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

int     taste_magic(unsigned char *input)
{
	int *value;
	int i;
	int val;

	value = (int *)malloc(4);
	i = -1;
	val = 3;
	*value = COREWAR_EXEC_MAGIC;
	while (++i < 4)
	{
		if (input[i] != ((unsigned char*)value)[val])
		{
			free(value);
			return (FAIL);
		}
		val--;
	}
	free(value);
	return (SUCCESS);
}

int     validate_binary(t_dsm *src_code)
{
	if (src_code->file_len < 4 || !taste_magic(src_code->input))
		return (err_validate(src_code));
	src_code->current_position = 4;
	if (!fill_name(src_code))
		return (err_validate(src_code));
	if (!fill_code_size(src_code))
		return (err_validate(src_code));
	if (!fill_comment(src_code))
		return (err_validate(src_code));
	if (!fill_diff_code_size(src_code))
		return (err_validate(src_code));
	free(src_code->input);
	return (SUCCESS);
}

int     read_my_binary(char *str, unsigned char **buf)
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