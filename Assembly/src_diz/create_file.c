//
// Created by Grass Emerald on 06/03/2020.
//

#include "asm.h"



int         take_new_name(t_dsm *src_code, char *old_name)
{
	int i;

	i = 0;
	if (!((src_code->file_name) = (char *)malloc(ft_strlen(old_name) + 1)))
		return (FAIL);
	while (old_name[++i] && old_name[i] != '.')
	{
		(src_code->file_name)[i] = old_name[i];
		i++;
	}
	(src_code->file_name)[i++] = '.';
	(src_code->file_name)[i++] = 's';
	(src_code->file_name)[i++] = '\0';
	return (SUCCESS);
}

int         fill_new_file(t_dsm *src_code)
{
	int fd;

	if ((fd = open(src_code->file_name,  O_CREAT | O_TRUNC | O_WRONLY, 0644)) < 1)
	{
		free(src_code->file_name);
		return (FAIL);
	}
	ft_putstr_fd(src_code->output, fd);
	close(fd);
	free(src_code->file_name);
	return (SUCCESS);
}