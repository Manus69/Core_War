/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:20:42 by selly             #+#    #+#             */
/*   Updated: 2019/11/04 13:28:50 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h" /////++++++

unsigned long	rem_sign_l(long double num, int *flag)
{
	unsigned long		new;

	*flag = num >= 0 ? 0 : 1;
	new = num < 0 ? -num : num;
	return (new);
}

long			rem_sign(long num, int *flag)
{
	*flag = num >= 0 ? 0 : 1;
	num = num < 0 ? -num : num;
	return (num);
}

char			*read_num(int *s, va_list ap, int *f)
{
	char			*str;
	long long		test;

	str = NULL;
	if (s[3] == 1)
	{
		test = rem_sign((signed short)va_arg(ap, signed int), &(*f));
		str = ft_itoa(test);
	}
	else if (s[3] == 2)
		str = ft_itoa_long(rem_sign_l(va_arg(ap, long), &(*f)));
	else if (s[3] == 22)
	{
		test = rem_sign_l(va_arg(ap, long long), &(*f));
		str = ft_itoa_long(test);
	}
	else if (s[3] == 11)
	{
		test = (signed char)va_arg(ap, signed int);
		str = ft_itoa(rem_sign(test, &(*f)));
	}
	else if (s[3] == 0)
		str = ft_itoa_long(rem_sign(va_arg(ap, int), &(*f)));
	return (str);
}

int				print_prefix_1(int times, char prefix, int *n)
{
	int		read;

	read = 0;
	while (times > 0)
	{
		read += ft_putchar_mod(prefix, n);
		times--;
	}
	return (read);
}

static int			a_print(int *new, int d, char *str, int count)
{
	int		spaces;
	int		nool;

	spaces = new[1] - new[2] - 1;
	if (!f_f(new[0], 3))
		print_prefix_1(spaces, ' ', new);
	if (d)
		ft_putchar_mod('-', new);
	else
		ft_putchar_mod('+', new);
	nool = new[2] - count;
	print_prefix_1(nool, '0', new);
	ft_putstr_mod(str,new[7]);
	if (f_f(new[0], 3))
		print_prefix_1(spaces, ' ', new);
	ft_strdel(&str);
	return (new[1]);
}

int			wight_and_accur(int **s, int d, int *w, int len)
{
	int		*new;
	int		buf;
	int		read;

	new = *s;
	buf = *w;
	read = 0;
	if (f_f(new[0], 2) && new[2] + 1 > len && f_f(new[0], 5))
		new[2] = new[2] + 1;
	if (f_f(new[0], 2) && f_f(new[0], 5) && d)
		new[1] = new[1] + 1;
	buf = new[1] - new[2];
	if (d || f_f(new[0], 4))
		buf--;
	if (d == 0 && new[1] > len && new[2] > len && f_f(new[0], 2) > 0 &&
			f_f(new[0], 4) > 0 && f_f(new[0], 5) > 0)
		buf++;
	if (f_f(new[0], 3) != 1)
		read += print_prefix_1(buf, ' ', new);
	*w = buf;
	return (read);
}

int				check_general_one(int **s, int d, int *w, int len)
{
	int		*new;
	int		read;

	read = 0;
	new = *s;
	if ((new[1] > len) && (new[2] > len) && (new[1] > new[2]))
		read += wight_and_accur(&(*s), d, &(*w), len);
	else if ((new[1] > len) && (new[1] > new[2]) && !(f_f(new[0], 2)))
	{
		*w = new[1] - len;
		if (f_f(new[0], 3) != 1)
			read += print_prefix_1(new[1] - len, ' ', new);
	}
	else if (f_f(new[0], 2) && new[2] > 0 && new[1] >
											 len && new[1] > new[2])
	{
		*w = new[1] - len;
		if (f_f(new[0], 3) != 1)
			read += print_prefix_1(new[1] - len, ' ', new);
	}
	return (read);
}

int				check_general_two(int **s, int d, int *w, int len)
{
	int		*new;
	int		read;

	new = *s;
	read = 0;
	if (new[2] > len)
	{
		if (d || f_f(new[0], 4))
		{
			if (!(f_f(new[0], 2) && f_f(new[0], 5)))
				len--;
		}
		if (f_f(new[0], 2) && new[1] < new[2] && f_f(new[0], 5))
			len--;
		read += print_prefix_1(new[2] - len, '0', new);
	}
	else if (new[1] > len && new[2] == -1 && f_f(new[0], 2))
	{
		if (f_f(new[0], 3))
			*w += new[1] - len;
		else
			read += print_prefix_1(new[1] - len, '0', new);
	}
	return (read);
}

int			check_general_three(int **s, int d, int *len, int *w)
{
	int		*new;
	int		read;

	read = 0;
	new = *s;
	if ((!d && (new[2] > new[1]) && f_f(new[0], 2)) ||
		(f_f(new[0], 3) || (new[2] > new[1])) ||
		(f_f(new[0], 2) && new[2] <= 0) ||
		(f_f(new[0], 2) && new[1] > new[2] && new[2] > *len))
		read += ft_putchar_mod(' ', new);
	(*w)--;
	if (f_f(new[0], 2))
		*len = *len + 1;
	return (read);
}

int				general_wigt_ac(int **s, int d, int *w, char *str)
{
	int		read;
	int		*new;
	int		len;

	read = 0;
	new = *s;
	len = ft_strlen_mod(str) + d;
	(!d && f_f(new[0], 4)) ? len++ : len;
	read += check_general_one(&new, d, w, len);
	if (d)
		read += ft_putchar_mod('-', new);
	else if (f_f(new[0], 4))
	{
		if (*str == '0' && (new[2] == -2 || new[2] == -3) && new[1] > 0 &&
			!(f_f(new[0], 3)))
			read += ft_putchar_mod(' ', new);
		read += ft_putchar_mod('+', new);
	}
	else if (f_f(new[0], 5))
		read += check_general_three(&new, d, &len, w);
	read += check_general_two(&new, d, w, len);
	return (read);
}

int			print_and_format_one(int **s, int d)
{
	int		*new;
	int		read;

	new = *s;
	read = 0;
	if (f_f(new[0], 4) && !d)
		read += ft_putchar_mod('+', new);
	else if (f_f(new[0], 5) && !d)
		read += ft_putchar_mod(' ', new);
	if (d)
		read += ft_putchar_mod('-', new);
	return (read);
}

int			print_and_format_two(int **s)
{
	int		*new;
	int		read;

	new = *s;
	read = 0;
	if (new[1] > 0 && !(f_f(new[0], 4)))
		read += ft_putchar_mod(' ', new);
	else if (new[1] > 0 && f_f(new[0], 4) && f_f(new[0], 3))
		read += ft_putchar_mod(' ', new);
	return (read);
}

int			print_and_format(int **s, int read, char *str, int d)
{
	int		*new;
	int		w;
	int		len;

	new = *s;
	w = 0;
	len = ft_strlen_mod(str) + d;
	(!d && f_f(new[0], 4)) ? len++ : len;
	if ((new[1] > len) || (new[2] > len))
		read += general_wigt_ac(&(*s), d, &w, str);
	else
		read += print_and_format_one(&new, d);
	if (*str == '0' && (new[2] == -2 || new[2] == -3))
		read += print_and_format_two(&new);
	else
		read += ft_putstr_mod(str, new[7]);
	if (f_f(new[0], 3))
	{
		if (f_f(new[0], 4) != 1 && !(d) && new[2] > 0 &&
				f_f(new[0], 2) > 0 && f_f(new[0], 5)
								  > 0 && new[2] > len)
			w = w + 1;
		read += print_prefix_1(w, ' ', new);
	}
	return (read);
}

int			work_with_int(int **s, va_list ap, int read, char *flag)
{
	int		*new;
	int		d;
	char	*str;
	int		len;

	new = *s;
	if (!flag)
	{
		if (!(str = read_num(*s, ap, &d)))
			return (print_warning(1));
	}
	else
	{
		str = flag;
		d = 0;
	}
	len = ft_strlen_mod(str) + d;
	if ((f_f(new[0], 4) > 0 || d == 1) &&
		new[1] > new[2] && ((new[2] == len) || (new[2] == len + 1)))
		return (a_print(new, d, str, ft_strlen(str)));
	read = print_and_format(&(*s), read, str, d);
	if (!flag)
		ft_strdel(&str);
	return (read);
}
