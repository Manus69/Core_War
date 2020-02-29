//
// Created by Grass Emerald on 29/02/2020.
//

#ifndef ASSEMBLY_DIZ_ASM_H
# define ASSEMBLY_DIZ_ASM_H

typedef struct  s_dsm
{
	char        *input;
	size_t      file_len;
	size_t      current_position;
}               t_dsm;

int     read_my_binary(char *str, char **buf);
char				*ft_binary_read(int fd, size_t *len);
int     validate_binary(t_dsm *src_code);

#endif //ASSEMBLY_DIZ_ASM_H
