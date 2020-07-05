/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:08:43 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 19:20:39 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "op.h"
# include "printf.h"
# include "diz_asm.h"
# include "function_prototypes.h"
# include "generic_list.h"
# include "tokens.h"
# include <fcntl.h>

# define ERR_READ 0
# define ERR_OPEN 0
# define MISS_MATCH 0
# define SUCCESS 1
# define TO_TRANSLATE 1
# define TO_DIZASM 2
# define ERR_USAGE 3
# define FAIL 0

int					take_name(int ac, char **av, int *arg_count,
					t_flag *has_flag);
int					asm_s(char *str, t_flag *has_flag);
int					to_translate(char *str);
int					to_dizasm(char *str);
int					err_usage(char *str, t_flag *has_flag);
int					dizasm(char *str, t_flag *has_flag);
int					err_out(char *str, t_flag *has_flag);

#endif
