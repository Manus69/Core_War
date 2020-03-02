//
// Created by Grass Emerald on 29/02/2020.
//

#ifndef ASSEMBLY_DIZ_ASM_H
# define ASSEMBLY_DIZ_ASM_H

typedef struct s_byte
{
	unsigned char name[PROG_NAME_LENGTH + 1];
	unsigned char comment[COMMENT_LENGTH + 1];
	size_t          champ_size;
}               t_translate;

typedef struct  s_dsm
{
	unsigned char        *input;
	size_t          file_len;
	size_t         current_position;
	t_translate  fill_file;
}               t_dsm;

typedef struct s_op
{
	char *op_name;
	int    arg_type_code;
	int     arg_type[3];
	int     op_code;
	int     cycle_before_use;
	char    *op_descript;
	int         carry_flag;
	int         size_t_dir;
}               t_op;

int     read_my_binary(char *str, unsigned char **buf);
unsigned char				*ft_binary_read(int fd, size_t *len);
int     validate_binary(t_dsm *src_code);
int     fill_name(t_dsm *src_code);
int     fill_comment(t_dsm *src_code);
int     fill_code_size(t_dsm *src_code);
int     fill_diff_code_size(t_dsm *src_code);

#endif //ASSEMBLY_DIZ_ASM_H
