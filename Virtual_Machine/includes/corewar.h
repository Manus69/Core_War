#ifndef COREWAR_H
# define COREWAR_H

# include "printf.h"
# include "op.h"
# include "error.h"

/*
 *  Структура для всей инфы о чемпионе, вставляется внутрь арены
 */

typedef struct 				s_champion
{
	int 					number;			// uniq player number, for example Player 1 or Player 2
	char 					*name;			// Player`s name *str
	int32_t 				pl_size;		// Player`s exec code size
	uint8_t 				*code;			// Player`s code, all options and args in 8-bytes format
	char 					*comment;		// Player`s comment *str
	struct s_champion		*next;			// next champion
}							t_champion;

/*
 *  Структура для всей инфы о каретке, вставляется внутрь арены
 */

typedef struct				s_slider
{
	int 					id; //номер чеспиона от которого произошла каретка
	int 					carry; //значение carry для прыжка
	uint8_t 				code; //байт кода
	ssize_t 				last_live; //последний раз выполненная операция live
	int 					circles_to_exec; //циклов до выхода
	uint8_t					type_of_args[3]; //типы агрументов
	int32_t					pc; // положение каретки
	uint32_t				step; //шаг
	int32_t					r[REG_NUMBER]; //регистры
	t_champion				*player; // чемпион
	struct s_slider			*next;
}							t_slider;

/*
 *  Структура для основной игры и создания арены, можно добавлять нужные переменные
 */

typedef struct 				s_arena
{
	int 					read_arg;		// был ли считан аргумент который надо записать в файл чемпиона
	int 					players;		// number of players. always: players <= MAX_PLAYERS !
	int 					read_num;		// for flag n;
	ssize_t 				cycles;			// count of cycles
	t_slider				*slider; 		// каретки
	int 					num_slider;		// число кареток
	ssize_t 				lives;			// число выполненных операций live
	ssize_t 				c_after_check;	// циклов после проверки
	size_t 					d_dump;			// for flag -d or -dump
	size_t 					show;			//for -s
	int 					aff_print;		// true(1) or false(0) for flag -a
	int 					visual;			// true(1) or false(0) for flag -v
	int 					print_type;		// bytes per line a) type == 1 -d 64 bytes in line b) type == 2 -dump 32 bytes in line
	int 					death_coming;	// CYCLES_TO_DEATH, countdown to death *evil_smile*
	t_champion				*last_alive;	// last alive player, may be winner.. or not?
	t_champion				*champion;		// link to players list, Pl-3 in the head of the list
	t_champion				*ch[MAX_PLAYERS]; // игроки по порядку
	uint8_t 				map[MEM_SIZE];	// memory for arena
}							t_arena;

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
t_slider					*init_slider(t_arena *vm, int	id, int place);
int 						check_player_id(t_arena *vm, int type);					//проверяет уникальность номера игрока, работает по-разному в зависимости от флага type 1) при type == 1: если номер (player id) повторяется, ф-ция выводит ошибку и заканчивает работу программы 2) если type == 0: при совпадении id выдает false, т/е возвращет 0, но продолжает работу.
t_arena						*set_player_id(t_arena *vm);							//устанавливает уникальные id тем игрокам, у которых id не заданы флагом -n

/*
 * 	Очистка памяти и вывод ошибок
 */

void						free_arena(t_arena **arena);							//free all structures
void						print_error(char	*error, t_arena *vm);				//different errors and free memory
void						print_mem_status(t_arena *vm);

#endif