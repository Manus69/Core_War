/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 01:11:07 by selly             #+#    #+#             */
/*   Updated: 2020/06/08 18:52:35 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

# include "printf.h"
# include "op.h"
# include "error.h"
# include "visual.h"

# define REG_NAME_SIZE		1

static uint8_t const	g_arg_code[3] = {
	T_REG,
	T_DIR,
	T_IND
};

typedef struct		s_champ
{
	int				num;
	char			*name;
	int32_t			size;
	uint8_t			*code;
	char			*comment;
	size_t			live;
	size_t			lives_before;
	ssize_t			last_live;
	struct s_champ	*next;
}					t_champ;

typedef struct		s_slider
{
	int				id;
	uint32_t		carry;
	uint8_t			code;
	ssize_t			last_live;
	ssize_t			cool_down;
	unsigned int	type_of_args[3];
	int32_t			place;
	uint32_t		step;
	int				write;
	int32_t			r[REG_NUMBER];
	t_champ			*player;
	struct s_slider	*next;
}					t_slider;

typedef struct		s_data
{
	int32_t			i;
	ssize_t			wait_store;
	ssize_t			wait_live;
	t_champ			*live;
}					t_data;

typedef struct		s_viz
{
	WINDOW			*win;
	WINDOW			*w_info;
	int				x;
	int				y;
	int				i;
	int				k;
	int				key;
	int				go;
	int				speed;
	int				place;
	clock_t			time;
	t_data			map[MEM_SIZE];
	char			aff;
	t_champ			*aff_champ;
}					t_viz;

typedef struct		s_arena
{
	int				read_arg;
	int				players;
	int				read_num;
	ssize_t			cycles;
	ssize_t			checks;
	t_slider		*slider;
	size_t			num_slider;
	ssize_t			lives;
	ssize_t			c_after_check;
	ssize_t			d_dump;
	size_t			show;
	int				aff_print;
	int				visual;
	int				nice;
	int				print_type;
	int				death;
	t_champ			*last;
	t_champ			*champion;
	t_champ			*ch[MAX_PLAYERS];
	t_viz			*viz;
	int				color[MEM_SIZE];
	uint8_t			map[MEM_SIZE];
}					t_arena;

typedef struct		s_oper
{
	char			*name;
	int				mod;
	uint8_t			code;
	int				vars;
	unsigned int	args_num;
	int				read_args;
	unsigned int	args_type[3];
	uint8_t			args_code[9];
	int				change_carry;
	ssize_t			cool_down;
	uint8_t			size_t_dir;
	void			(*operation)(t_arena *, t_slider *);
}					t_oper;

int					main(int argc, char **argv);
t_arena				*check_input(char **argv, int argc, t_arena *vm);
t_arena				*get_champion(char *argv, t_arena *vm);

void				usage(int type, int nice);
void				credits();

t_arena				*init_arena(void);
int32_t				get_magic(int fd, t_arena *vm);
t_champ				*init_player(int id, t_arena *vm);
t_slider			*init_slider(t_arena *vm, int	id, int p, int flag);
int					check_player_id(t_arena *vm, int type);
t_arena				*set_player_id(t_arena *vm);

void				free_arena(t_arena **arena);
void				print_error(char	*error, t_arena *vm);
void				print_err_size(char *file, t_arena *vm);
void				print_mem_status(t_arena *vm);

void				start_war(t_arena *vm);
int					is_op(int8_t byte);
int8_t				read_byte(t_arena *vm, int32_t place, int32_t step);
uint32_t			step(t_slider *cursor, t_oper *op);
t_slider			*write_args_types(t_slider *s, t_oper *o, int8_t c);
void				rw_memory(t_arena *v, t_slider *sl, int s, t_oper *p);
void				read_args_size(t_arena *vm, t_slider *s, t_oper *op);
int32_t				read_mem(t_arena *v, t_slider *s, uint8_t i, t_oper *o);
int32_t				bytes_to_magic(const uint8_t *mag, int32_t pl, size_t size);
void				magic_to_byte(uint8_t *m, int32_t p, int32_t v, int32_t s);
void				put_color(int *col, int32_t place, t_slider *sl, int32_t s);
int32_t				find_place(int32_t place);
t_slider			*copy_slider(t_arena *vm, t_slider *sl, int32_t addr);
uint32_t			next_step(uint8_t arg_type, t_oper *op);
void				cycles_to_die_check(t_arena *vm);

void				show_war(t_arena *vm);
t_viz				*new_viz(t_arena *vm);
void				put_data(t_arena *vm);
void				set_key(t_arena *vm);
void				clear_slider(t_arena *vm, t_slider *sl);
void				draw_slider(t_arena *vm, t_slider *sl);
void				update_map(t_arena *vm, t_slider *sl, int32_t p, int32_t s);
void				draw(t_arena *vm);
void				draw_info(t_arena *vm);

void				draw_winner(t_arena *vm);
void				draw_aff(t_arena *vm);
void				draw_menu_1(t_arena *vm);
void				draw_players(t_arena *vm);
void				init_colors(void);
void				init_sl(t_arena *vm);
void				init_map(t_arena *vm);

void				live(t_arena *vm, t_slider *sl);
void				ld(t_arena *vm, t_slider *sl);
void				st(t_arena *vm, t_slider *sl);
void				add(t_arena *vm, t_slider *sl);
void				sub(t_arena *vm, t_slider *sl);
void				and(t_arena *vm, t_slider *sl);
void				or(t_arena *vm, t_slider *sl);
void				xor(t_arena *vm, t_slider *sl);
void				zjmp(t_arena *vm, t_slider *sl);
void				ldi(t_arena *vm, t_slider *sl);
void				sti(t_arena *vm, t_slider *sl);
void				lld(t_arena *vm, t_slider *sl);
void				lldi(t_arena *vm, t_slider *sl);
void				lfork(t_arena *vm, t_slider *sl);
void				aff(t_arena *vm, t_slider *sl);
void				fork_op(t_arena *vm, t_slider *sl);

void				show_mem(t_arena *vm);
void				inroduction(t_champ *ch[4], int count, int nice, int i);

static t_oper	const	g_operation_list[16] = {
	{
		.name = "live",
		.mod = 0,
		.code = 0x01,
		.vars = 1,
		.args_num = 1,
		.args_code = {0x80, 0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_DIR, 0, 0},
		.change_carry = 0,
		.read_args = 0,
		.size_t_dir = 4,
		.cool_down = 10,
		.operation = &live,
	},
	{
		.code = 0x02,
		.name = "ld",
		.mod = 1,
		.args_num = 2,
		.vars = 2,
		.args_code = {0x90, 0xd0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_DIR | T_IND, T_REG, 0},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 5,
		.operation = &ld,
	},
	{
		.code = 0x03,
		.name = "st",
		.args_num = 2,
		.vars = 2,
		.args_code = {0x50, 0x70, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_REG, T_REG | T_IND, 0},
		.change_carry = 0,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 5,
		.operation = &st,
	},
	{
		.code = 0x04,
		.name = "add",
		.args_num = 3,
		.vars = 1,
		.args_code = {0x54, 0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_REG, T_REG, T_REG},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 10,
		.operation = &add,
	},
	{
		.code = 0x05,
		.name = "sub",
		.args_num = 3,
		.vars = 1,
		.args_code = {0x54, 0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_REG, T_REG, T_REG},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 10,
		.operation = &sub,
	},
	{
		.code = 0x06,
		.name = "and",
		.mod = 1,
		.args_num = 3,
		.vars = 6,
		.args_code = {0xa4, 0xb4, 0x94, 0xe4, 0xf4, 0xd4, 0x64, 0x74, 0x54},
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 6,
		.operation = &and,
	},
	{
		.code = 0x07,
		.name = "or",
		.mod = 1,
		.args_num = 3,
		.vars = 6,
		.args_code = {0xa4, 0xb4, 0x94, 0xe4, 0xf4, 0xd4, 0x64, 0x74, 0x54},
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 6,
		.operation = &or,
	},
	{
		.code = 0x08,
		.name = "xor",
		.mod = 1,
		.args_num = 3,
		.vars = 6,
		.args_code = {0xa4, 0xb4, 0x94, 0xe4, 0xf4, 0xd4, 0x64, 0x74, 0x54},
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR | T_IND, T_REG},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 6,
		.operation = &xor,
	},
	{
		.code = 0x09,
		.name = "zjmp",
		.mod = 1,
		.args_num = 1,
		.vars = 1,
		.args_code = {0x80, 0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_DIR, 0, 0},
		.change_carry = 0,
		.read_args = 0,
		.size_t_dir = 2,
		.cool_down = 20,
		.operation = &zjmp,
	},
	{
		.code = 0x0a,
		.name = "ldi",
		.mod = 1,
		.args_num = 3,
		.vars = 6,
		.args_code = {0xa4, 0x94, 0xe4, 0xd4, 0x64, 0x54, 0, 0, 0},
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.change_carry = 0,
		.read_args = 1,
		.size_t_dir = 2,
		.cool_down = 25,
		.operation = &ldi,
	},
	{
		.code = 0x0b,
		.name = "sti",
		.mod = 1,
		.args_num = 3,
		.vars = 6,
		.args_code = {0x68, 0x64, 0x78, 0x74, 0x58, 0x54, 0, 0, 0},
		.args_type = {T_REG, T_REG | T_DIR | T_IND, T_REG | T_DIR},
		.change_carry = 0,
		.read_args = 1,
		.size_t_dir = 2,
		.cool_down = 25,
		.operation = &sti,
	},
	{
		.code = 0x0c,
		.name = "fork",
		.mod = 1,
		.args_num = 1,
		.vars = 1,
		.args_code = {0x80, 0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_DIR, 0, 0},
		.change_carry = 0,
		.read_args = 0,
		.size_t_dir = 2,
		.cool_down = 800,
		.operation = &fork_op,
	},
	{
		.code = 0x0d,
		.name = "lld",
		.mod = 0,
		.args_num = 2,
		.vars = 2,
		.args_code = {0x90, 0xd0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_DIR | T_IND, T_REG, 0},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 10,
		.operation = &lld,
	},
	{
		.code = 0x0e,
		.name = "lldi",
		.mod = 1,
		.args_num = 3,
		.vars = 6,
		.args_code = {0xa4, 0x94, 0xe4, 0xd4, 0x64, 0x54, 0, 0, 0},
		.args_type = {T_REG | T_DIR | T_IND, T_REG | T_DIR, T_REG},
		.change_carry = 1,
		.read_args = 1,
		.size_t_dir = 2,
		.cool_down = 50,
		.operation = &lldi,
	},
	{
		.code = 0x0f,
		.name = "lfork",
		.mod = 1,
		.args_num = 1,
		.vars = 1,
		.args_code = {0x80, 0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_DIR, 0, 0},
		.change_carry = 0,
		.read_args = 0,
		.size_t_dir = 2,
		.cool_down = 1000,
		.operation = &lfork,
	},
	{
		.code = 0x10,
		.name = "aff",
		.args_num = 1,
		.vars = 1,
		.args_code = {0x40, 0, 0, 0, 0, 0, 0, 0, 0},
		.args_type = {T_REG, 0, 0},
		.change_carry = 0,
		.read_args = 1,
		.size_t_dir = 4,
		.cool_down = 2,
		.operation = &aff,
	}
};

#endif
