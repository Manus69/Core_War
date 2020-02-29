#ifndef COREWAR_H
# define COREWAR_H

# include "printf.h"
# include "op.h"

typedef struct 		s_champion
{
	int 			number;			// unic player number, for example Player 1 or Player 2
	char 			*name;			// Player`s name
	int32_t 		pl_size;		// Player`s exec code size
	int8_t 			*code;			// Player`s code, all options and args
	char 			*comment;		// Player`s comment
	struct s_pl		*next;			// next champion
}					t_champion;

/*
 *  May be we`ll do all (or some) int-types variables in arena to size_t types?
 *  I`m not sure about it..
 */

typedef struct 		s_arena
{
	int 			players;		// number of players. always-> players <= MAX_PLAYERS !
	int 			cycles;			// count of cycles
	int 			d_num;			// for flag -d or -dump a) d_num == 1 if -d; b) d_num == 2 for -dump
	int 			aff_print;		// true(1) or false(0) for flag -a
	int 			visual;			// true(1) or false(0) for flag -v
	int 			print_type;		// bytes per line a) type == 1 -d 64 bytes in line b) type == 2 -dump 32 bytes in line
	int 			death_comming;	// CYCLES_TO_DEATH, countdown to death *evil_smile*
	t_champion		last_alive;		// last alive player, may be winner.. or not?
	t_champion		*champion;		// link to players list, Pl-3 in the head of list
	int8_t 			*map[MEM_SIZE];	//	memory for arena

}					t_arena;

int		main(int argc, char **argv);
void	test(char *n);


#endif