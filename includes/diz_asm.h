/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diz_asm.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:09:33 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 19:28:41 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIZ_ASM_H
# define DIZ_ASM_H
# include <stdlib.h>

# define OUTPUT_LEN 10000

typedef struct		s_flag
{
	int				flag_a;
	int				visible;
	int				change_name;
	char			*new_file_name;
	char			*file_name;
}					t_flag;

typedef struct		s_byte
{
	unsigned char	name[PROG_NAME_LENGTH + 1];
	unsigned char	comment[COMMENT_LENGTH + 1];
	size_t			champ_size;
}					t_translate;

typedef struct		s_dsm
{
	char			*file_name;
	unsigned char	*input;
	size_t			file_len;
	size_t			current_position;
	t_translate		fill_file;
	char			*output;
	size_t			output_position;
}					t_dsm;

typedef struct		s_op
{
	char			*op_name;
	int				arg_count;
	int				arg_type[3];
	int				op_code;
	int				cycle_before_use;
	char			*op_descript;
	int				arg_code_flag;
	int				size_t_dir;
}					t_op;

static				t_op const g_op_tab[17] =\
{{0, 0, {0}, 0, 0, 0, 0, 0},
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0}
};

typedef struct		s_argum
{
	int				args_count;
	int				arg_type[3];
	int				arg_size[3];
}					t_argum;

void				print_binary_stdout(t_dsm *src_code);
void				print_alone_byte(t_dsm *src_code);

int					read_my_binary(char *str, unsigned char **buf);
unsigned char		*ft_binary_read(int fd, size_t *len);
int					validate_binary(t_dsm *src_code, t_flag *has_flag);
int					fill_name(t_dsm *src_code);
int					fill_comment(t_dsm *src_code);
int					fill_code_size(t_dsm *src_code);
int					fill_diff_code_size(t_dsm *src_code);
int					collect_pre_print(t_dsm *src_code);
int					put_name_comment(t_dsm *src_code);
int					walk_throw(t_dsm *src_code);
int					fill_complex_instruction(t_dsm *src_code, t_argum *args);
int					write_instruction(t_dsm *src_code, int op_code);
int					fill_simple_instruction(t_dsm *src_code);
char				*take_short_dir(t_dsm *src_code);
char				*take_simple_dir(t_dsm *src_code);
int					fill_new_file(t_dsm *src_code, t_flag *has_flag);
int					take_new_name(t_dsm *src_code, char *old_name);
int					write_instruction(t_dsm *src_code, int op_code);
int					write_reg(t_dsm *src_code, t_argum *args, int j);
char				*take_short_dir(t_dsm *src_code);
char				*take_simple_dir(t_dsm *src_code);

t_flag				*free_structure(t_flag	*flag);
int					is_flag(char *test, t_flag *flag, int *count, char **av);

#endif
