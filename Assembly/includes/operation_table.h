#include "op.h"

#define NUMBER_OF_OPERATIONS 17

typedef struct      s_op
{
	char            *op_name;
	int             arg_count;
	int             arg_type[3];
	int             op_code;
	int             cycle_before_use;
	char             *op_descript;
	int             arg_code_flag;
	int             size_t_dir;
}                   t_op;

static t_op    op_tab[17] =
{
    {0, 0, {0}, 0, 0, 0, 0, 0},
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

enum e_operation_name
{
    dummy_operation,
    live_operation,
    ld_operation,
    st_operation,
    add_operation,
    sub_operation,
    and_operation,
    or_operation,
    xor_operation,
    zjmp_operation,
    ldi_operation,
    sti_operation,
    fork_operation,
    lld_operation,
    lldi_operation,
    lfork_operation,
    aff_operation,
};