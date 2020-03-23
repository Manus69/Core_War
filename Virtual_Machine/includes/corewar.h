#ifndef COREWAR_H
# define COREWAR_H

# include "printf.h"
# include "op.h"
# include "error.h"
# include "visual.h"

# define REG_NAME_SIZE 			1
/*
 *  Структура для всей инфы о чемпионе, вставляется внутрь арены
 */

static uint8_t			g_arg_code[3] = {
		T_REG,
		T_DIR,
		T_IND
};

typedef struct 				s_champion
{
	int 					number;				// uniq player number, for example Player 1 or Player 2
	char 					*name;				// Player`s name *str
	int32_t 				pl_size;			// Player`s exec code size
	uint8_t 				*code;				// Player`s code, all options and args in 8-bytes format
	char 					*comment;			// Player`s comment *str
	size_t					live;
	size_t					lives_before;
	ssize_t					last_live;
	struct s_champion		*next;				// next champion
}							t_champion;

/*
 *  Структура для всей инфы о каретке, вставляется внутрь арены
 */

typedef struct				s_slider
{
	int 					id;					// номер каретки
	uint32_t 				carry;				// значение carry для прыжка
	uint8_t 				code; 				// байт кода
	ssize_t 				last_live; 			// последний раз выполненная операция live
	ssize_t 				cool_down; 			// циклов до выполнения функции
	unsigned int			type_of_args[3];	// типы агрументов T_DIR - 1; T_IND - 2; T_REG - 3;
	int32_t					place;				// положение каретки
	uint32_t				step;				// шаг
	int 					write;				// были ли записаны аргументы
	int32_t					r[REG_NUMBER];		// регистры
	t_champion				*player;			// чемпион
	struct s_slider			*next;
}							t_slider;

/*
 *  Структура для основной игры и создания арены, можно добавлять нужные переменные
 */

typedef struct		s_data
{
	int32_t			i;
	ssize_t			wait_store;
	ssize_t			wait_live;
	t_champion		*live;
}					t_data;

typedef struct		s_viz
{
	WINDOW			*win;
	WINDOW			*w_info;
	WINDOW			*w_help;
	int 			x;
	int 			y;
	int 			i;
	int 			k;
	int				key;
	int				go;
	int				speed;
	int				place;
	clock_t			time;
	t_data			map[MEM_SIZE];
	char			aff;
	t_champion		*aff_champ;
	int				sound;
	int				help;
}					t_viz;

typedef struct 				s_arena
{
	int 					read_arg;			// был ли считан аргумент который надо записать в файл чемпиона
	int 					players;			// number of players. always: players <= MAX_PLAYERS !
	int 					read_num;			// for flag n;
	ssize_t 				cycles;				// count of cycles
	ssize_t 				checks;				// количество выполненных проверок
	t_slider				*slider; 			// каретки
	size_t 					num_slider;			// число кареток
	ssize_t 				lives;				// число выполненных операций live
	ssize_t 				c_after_check;		// циклов после проверки
	ssize_t 				d_dump;				// for flag -d or -dump
	size_t 					show;				// for -s
	int 					aff_print;			// true(1) or false(0) for flag -a
	int 					visual;				// true(1) or false(0) for flag -v
	int 					print_type;			// bytes per line a) type == 1 -d 64 bytes in line b) type == 2 -dump 32 bytes in line
	int 					death_coming;		// CYCLES_TO_DEATH, countdown to death *evil_smile*
	t_champion				*last_alive;		// last alive player, may be winner.. or not?
	t_champion				*champion;			// link to players list, Pl-3 in the head of the list
	t_champion				*ch[MAX_PLAYERS];	// игроки по порядку
	t_viz					*viz;				//для визуала
	int 					color[MEM_SIZE];
	uint8_t 				map[MEM_SIZE];		// memory for arena
}							t_arena;

typedef struct			s_operation
{
	char 				*name;									// название операции
	int 				mod;									// деление по модулю
	uint8_t 			code;									// код функции
	int 				vars;
	unsigned int		args_num;								// число принимаемых аргументов (от 1 до 3х)
	int 				read_args;								// 1 - есть инфо об аргументах (если их больше 1), 0 - только 1 арг-т, считывать не надо
	unsigned int		args_type[3];							// типы агрументов T_DIR - 1; T_IND - 2; T_REG - 3;
	uint8_t 			args_code[9];
	int 				change_carry;							// изменяет значение carry - 1; не изменяет carry - 0
	ssize_t				cool_down;									// кол-во циклов
	uint8_t 			size_t_dir;								// размер T_DIR
	void				(*operation)(t_arena *, t_slider *);	// ссылка на функцию операции
}						t_operation;

/*
 * Ниже - основные функции по порядку
 */

int							main(int argc, char **argv);							//let`s go..
t_arena 					*check_input(char **argv, int argc, t_arena *vm);		//check flags
t_arena						*get_champion(char 	*argv, t_arena *vm);				//read fd and parsing info from file.cor

/*
 * 	О программе, кто делал, как использовать, какие принимает флаги
 */

void						usage(int type);										//how use CoreWar
void						credits();												//about us

/*
 * 	Заполнение переменных, чтение и систематизация данных из бинарника
 */

t_arena						*init_arena(void);										//get new empty arena
int32_t						get_magic(int fd, t_arena *vm);							//read 8-bytes and convert it to 32
t_champion					*init_player(int id, t_arena *vm);						//init new empty champion
t_slider					*init_slider(t_arena *vm, int	id, int place, int flag);			//новая каретка
int 						check_player_id(t_arena *vm, int type);					//проверяет уникальность номера игрока, работает по-разному в зависимости от флага type 1) при type == 1: если номер (player id) повторяется, ф-ция выводит ошибку и заканчивает работу программы 2) если type == 0: при совпадении id выдает false, т/е возвращет 0, но продолжает работу.
t_arena						*set_player_id(t_arena *vm);							//устанавливает уникальные id тем игрокам, у которых id не заданы флагом -n

/*
 * 	Очистка памяти и вывод ошибок
 */

void						free_arena(t_arena **arena);							//free all structures
void						print_error(char	*error, t_arena *vm);				//different errors and free memory
void						print_mem_status(t_arena *vm);							//печатает арену

/*
 * 	Считывание и обработка кода чемпионов
 */

void						start_war(t_arena  *vm);
int 						is_op(int8_t byte);
int8_t 						read_byte(t_arena *vm, int32_t	place, int32_t step);
uint32_t					step(t_slider *cursor, t_operation *op);
t_slider					*write_args_types(t_slider *s, t_operation *op, int8_t code);
void						rw_memory(t_arena *vm, t_slider *sl, int sliders, t_operation *op);
void						read_args_size(t_arena *vm, t_slider *s, t_operation *op);
int32_t						read_mem(t_arena *vm, t_slider *s, uint8_t i, t_operation *op);
int32_t						bytes_to_magic(const uint8_t *magic, int32_t place,size_t size);
void						magic_to_byte(uint8_t *map, int32_t place, int32_t value, int32_t s);
void						put_color(int *color, int32_t place, t_slider *sl, int32_t s);
int32_t						find_place(int32_t place);
t_slider					*copy_slider(t_arena *vm, t_slider *sl, int32_t addr);
uint32_t					next_step(uint8_t arg_type, t_operation *op);
void						cycles_to_die_check(t_arena *vm);

/*
 * 	визуализация
 */



void						show_war(t_arena *vm);
t_viz						*new_viz(t_arena *vm);
void						put_data(t_arena *vm);
void						set_key(t_arena *vm);
void						clear_slider(t_arena *vm, t_slider *sl);
void						draw_slider(t_arena *vm, t_slider *sl);
void						update_map(t_arena *vm, t_slider *sl, int32_t place, int32_t s);
void						draw(t_arena *vm);
void						draw_info(t_arena *vm);

void					draw_winner(t_arena *vm);
void					draw_aff(t_arena *vm);
void					draw_menu(t_arena *vm);
void					draw_players(t_arena *vm);
void					init_colors(void);
void					init_sl(t_arena *vm);
void					init_map(t_arena *vm);

/*
 * 	функции операций
 */

void		live(t_arena *vm, t_slider *sl);
void		ld(t_arena *vm, t_slider *sl);
void		st(t_arena *vm, t_slider *sl);
void		add(t_arena *vm, t_slider *sl);
void		sub(t_arena *vm, t_slider *sl);
void		and(t_arena *vm, t_slider *sl);
void		or(t_arena *vm, t_slider *sl);
void		xor(t_arena *vm, t_slider *sl);
void		zjmp(t_arena *vm, t_slider *sl);
void		ldi(t_arena *vm, t_slider *sl);
void		sti(t_arena *vm, t_slider *sl);
void		lld(t_arena *vm, t_slider *sl);
void		lldi(t_arena *vm, t_slider *sl);
void		lfork(t_arena *vm, t_slider *sl);
void		aff(t_arena *vm, t_slider *sl);
void		fork_op(t_arena *vm, t_slider *sl);
void		play_sound(t_arena *vm, char flag);

/*
 * 	структуры операций
 */

static t_operation			operation_list[16] = {
		{
			.code = 0x01,
			.name = "live",
			.mod = 0,
			.args_num = 1,
			.vars = 1,
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