//
// Created by Grass Emerald on 29/02/2020.
//

#include "asm.h"

int     read_my_binary(char *str, char **buf)
{
	int fd;
	int ret;

	if ((fd = open(str, O_RDONLY)) < 0)
		return (err_out("ERROR : FILE DOES NOT EXIST"));
	if (!((*buf) = (char *)malloc(1000000)))
		return (err_out("ERROR : CAN'T MEMALLOC"));
	if ((ret = read(fd, (*buf), 1000000)) < 0)
	{
		free((*buf));
		return (err_out("ERROR : CAN'T READ FILE"));
	}
//	(*buf)[ret] = '\0';
	return (1);
}