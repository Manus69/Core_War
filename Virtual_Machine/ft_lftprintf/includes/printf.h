/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 14:39:57 by selly             #+#    #+#             */
/*   Updated: 2019/10/24 16:42:15 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdarg.h>
#include "libft/libft.h"

int			ft_printf(const char *format, ...);
int		    format_str(const char *format, va_list ap, int **conv, int symbols);
//int			read_flags(va_list ap, const char *p, int *i);

int			check_flag(const char **p, int flag_id);
int			check_wight(const char **p);
int			check_accuracy(const char **p);
int			check_type(const char **p);
int			check_conv(const char **p);

int			format_args(int **s, va_list ap);
int			read_conv(va_list ap, const char **p, int **s, int end);

int         work_with_chars(int **s, va_list ap, int read, char *empty);
int			work_with_pointer(int **s, va_list ap, int read);
int			work_with_int(int **s, va_list ap, int read, char *flag);
int			work_with_o(int **s, va_list ap, int read);
int			work_with_x(int **s, va_list ap, int read); //const char **p заменил на read
int			work_with_x_big(int **s, va_list ap, int read);
int			work_with_u(int **s, va_list ap, int read);
int 		work_with_floats(int **s, va_list ap, int read);
//int 		work_with_x(int **s, va_list ap, int read);
int			f_f(int flags, int flag_id);

void		print_last_spaces(int **num, int flag, int len);
int			f_f(int flags, int flag_id);
char		*read_num(int   *s, va_list ap, int *flag);
int 		all_flags(int *s);

//void		print_err(int  error);
//int			print_prefix(int times, char prefix, int *n);
int			print_warning(int warning);
//int     	ft_putnbr_base_n(long long nbr, int base);

//int         print_spaces(char space, int times);

void     ft_putnbr_base_p(unsigned long long nbr, int base, int flag, int *s); //put_char base 2/8/10/16
int     ft_putnbr_base_c(unsigned long long nbr, int base); // count char* in base 2/8/10/16

//функции для форматов u x o
void write_new_one(int i, int *n);
void if_minus_off_part_two(int **s, unsigned long d, int count);
void if_minus_off_part_one(int **s, unsigned long d, int count);
int true_score(int **s, unsigned long d, int count, int base);
int if_flags_more_d(int **s, unsigned long d, int count, int base);
int if_wight_more_acur(int **s, unsigned long d, int count, int base);
int if_minus_in_flag_off(int **s, unsigned long d, int count, int base);
int if_minus_in_flag_on(int **s, unsigned long d, int count, int base);
int wight_more_count(int **s, unsigned long d, int count, int base);
int wight_or_acur(int **s, unsigned long d, int count, int base);
int wight_or_acur_two(int **s, unsigned long d, int count, int base);
int work_x_o_u(int **s, unsigned long d, int count, int base);

//бонусы
int     get_bonus(const char **p);
int     get_color(const char **p);
int     find_id(const char **p, const char *end);
int     find_decor(const char **p);
void    start(char  *str, int flag);
int     ft_fprintf(char *file, const char *format, ...);
int     ft_vprintf(const char *format, va_list ap);

#endif
