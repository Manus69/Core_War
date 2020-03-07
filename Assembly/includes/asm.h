/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:08:43 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:09:25 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define FAIL 0

int			take_name(int ac, char **av);
int			asm_s(char *str);
int			dizasm(char *str);
int			err_out(char *str);

#endif
