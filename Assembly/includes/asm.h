//
// Created by Grass Emerald on 29/02/2020.
//

#ifndef ASSEMBLY_ASM_H
# define ASSEMBLY_ASM_H

# include "../../Resources/op.h"
# include "ft_printf.h"
# include "diz_asm.h"
# include <fcntl.h>

# define ERR_READ 0
# define ERR_OPEN 0
# define MISS_MATCH 0
# define SUCCESS 1
# define TO_TRANSLATE 1
# define TO_DIZASM 2
# define ERR_USAGE 3

int     take_name(int ac, char **av);
int asm_s(char *str);
int dizasm(char *str);
int     err_out(char *str);

#endif
