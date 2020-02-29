/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_with_floats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 14:32:04 by mnarwhal          #+#    #+#             */
/*   Updated: 2019/11/04 17:39:04 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h" /////укороть имена 3х функций остальное +++++

static int		int_l(unsigned long int n)
{
	int		size;

	size = 1;
	while (n /= 10)
		size++;
	return (size);
}

static void		reverse(char *str, int len)
{
	int		i;
	int		j;
	int		temp;

	i = 0;
	j = len - 1;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}

static int		i_to_s_i(int **s, unsigned long long x, char *str, int minus)
{
	int		i;
	int		*new;
	int		d;

	i = 0;
	new = *s;
	d = 0;
	x == 0 ? (str[i++] = '0') : (str[i]);
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d)
		str[i++] = '0';
	new[2] == -2 ? (new[2] = -1) : (new[2]);
	if (minus == 1 && new[1] > new[2] + 1 + int_l(x) + 1 && f_f(new[0],
			2) > 0 && f_f(new[0], 3) <= 0)
		while (new[1]-- > new[2] + int_l(x) + 2)
			str[i++] = '0';
	if (minus == 1)
		str[i++] = '-';
	reverse(str, i);
	str[i] = '\0';
	return (i);
}

static int			i_to_s(unsigned long long x, char *str, int d, int large)
{
	int		i;

	i = 0;
	if (x == 0)
		str[i++] = '0';
	if (large > 0)
		while (large-- > 0)
			str[i++] = '0';
	while (x)
	{
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	while (i < d)
		str[i++] = '0';
	reverse(str, i);
	str[i] = '\0';
	return (i);
}

static long double		ft_pow_m(int x, int n)
{
	long double		ext;
	int				i;

	ext = 1;
	i = 1;
	while (i <= n)
	{
		ext *= x;
		i++;
	}
	return (ext);
}

void			c_fp(long double *fp, int *large, unsigned long *ip, int *a_p)
{
	if (*a_p != 0)
	{
		if (*a_p >= 20 && *fp * ft_pow_m(10, 13) > 19 * ft_pow_m(10, 11))//18446744073709551615
		{
			*fp = *fp * ft_pow_m(10, 19);
			*large = *a_p - 19;
		}
		else
			*fp = (*fp * ft_pow_m(10, *a_p)) + 0.5;
	}
	if (*a_p == 0)
		*fp += 0.5;
	if (int_l(*fp) > int_l(ft_pow_m(10, *a_p - 1)) && *a_p < 20)
	{
		*ip = *ip + 1;
		*fp = *fp - ft_pow_m(10, *a_p);
	}
}

char				*ft_ftoa(int **s, long double n, int after_p, int minus)
{
	unsigned long int		ipart;
	long double				fpart;
	int						large;
	int						*new;
	char					*res;

	new = *s;
	large = 0;
	ipart = (unsigned long int)n;
	fpart = n - (long double)ipart;
	c_fp(&fpart, &large, &ipart, &after_p);
	res = (char*)malloc(sizeof(char) * 1000);
	ipart = i_to_s_i(&new, ipart, res, minus);
	if (after_p == 0)
		return (res);
	res[ipart] = '.';
	i_to_s(fpart, res + ipart + 1, after_p, large);
	return (res);
}

void			out_zero_float_one(int **s, char *str, int sight)
{
	int		*new;

	new = *s;
	if (f_f(new[0], 4) > 0 && sight == 0)
		ft_putchar_mod('+', new);
	ft_putstr_mod(str, new[7]);
	if (f_f(new[0], 1) > 0)
		ft_putchar_mod('.', new);
}

void			out_zero_float_two(int **s, char *str, int sight, int len)
{
	int			*new;

	new = *s;
	if (f_f(new[0], 5) > 0 && f_f(new[0], 4) <= 0 && sight == 0)
		len += ft_putchar_mod(' ', new);
	if (f_f(new[0], 4) > 0 && sight == 0)
		ft_putchar_mod('+', new);
	ft_putstr_mod(str, new[7]);
	if (f_f(new[0], 1) > 0)
		len += ft_putchar_mod('.', new);
	while (new[1] > len++)
		ft_putchar_mod(' ', new);
}

void			out_zero_float_three(int **s, char *str, int sight, int len)
{
	int			*new;

	new = *s;
	if (f_f(new[0], 4) > 0 && sight == 0 && f_f(new[0], 2) > 0)
		ft_putchar_mod('+', new);
	if (f_f(new[0], 5) > 0 && f_f(new[0], 4) <= 0 && sight == 0)
		len += ft_putchar_mod(' ', new);
	while (new[1] > len++)
	{
		if (f_f(new[0], 2) > 0 && sight == 0)
			ft_putchar_mod('0', new);
		else
			ft_putchar_mod(' ', new);
	}
	if (f_f(new[0], 4) > 0 && sight == 0 && f_f(new[0], 2) <= 0)
		ft_putchar_mod('+', new);
	ft_putstr_mod(str, new[7]);
	if (f_f(new[0], 1) > 0)
		ft_putchar_mod('.', new);
}

int				out_zero_float_new_one(int **s, char *str, int sight, int len)
{
	int		*new;

	new = *s;
	if (f_f(new[0], 3) > 0)
	{
		out_zero_float_two(&new, str, sight, len);
		return (new[1]);
	}
	else
	{
		out_zero_float_three(&new, str, sight, len);
		return (new[1]);
	}
}

static int		out_zero_float(int **s, char *str, int sight)
{
	int			*new;
	int			len;

	new = *s;
	len = ft_strlen(str);
	if (len > new[1])
	{
		out_zero_float_one(&new, str, sight);
		return (len);
	}
	else if (new[1] > len)
	{
		if (f_f(new[0], 4) > 0 && sight == 0)
			len++;
		return (out_zero_float_new_one(&new, str, sight, len));
	}
	return (0);
}

void			wight_more_one(int **s, int len, char *str, int sight)
{
	int		*new;

	new = *s;
	if (f_f(new[0], 5) > 0 && f_f(new[0], 4) <= 0 && sight == 0)
		len += ft_putchar_mod(' ', new);
	if (f_f(new[0], 4) > 0 && sight == 0)
		len += ft_putchar_mod('+', new);
	ft_putstr_mod(str, new[7]);
	while (new[1] > len++)
		ft_putchar_mod(' ', new);
}

void			wight_more_two(int **s, int len, char *str, int sight)
{
	int		*new;

	new = *s;
	if (f_f(new[0], 4) > 0 && sight == 0 && f_f(new[0], 2) > 0)
		ft_putchar_mod('+', new);
	if (f_f(new[0], 5) > 0 && f_f(new[0], 4) <= 0 && sight == 0)
		len += ft_putchar_mod(' ', new);
	while (new[1] > len++)
	{
		if (f_f(new[0], 2) > 0)
			ft_putchar_mod('0', new);
		else
			ft_putchar_mod(' ', new);
	}
	if (f_f(new[0], 4) > 0 && sight == 0 && f_f(new[0], 2) <= 0)
		ft_putchar_mod('+', new);
	ft_putstr_mod(str, new[7]);
}

int				float_wight_more(int **s, int len, char *str, int sight)
{
	int		*new;

	new = *s;
	if (f_f(new[0], 3) > 0)
	{
		wight_more_one(&new, len, str, sight);
		return (new[1]);
	}
	else
	{
		if (f_f(new[0], 4) > 0 && sight == 0)
			len++;
		wight_more_two(&new, len, str, sight);
		return (new[1]);
	}
}

int				out_non_zero(int **s, char *str, int sight)
{
	int		*new;
	int		len;

	new = *s;
	len = ft_strlen(str);
	if (len >= new[1])
	{
		if (f_f(new[0], 5) > 0 && f_f(new[0], 4) <= 0 && sight != 1)
			len += ft_putchar_mod(' ', new);
		if (f_f(new[0], 4) > 0)
			len++;
		if (f_f(new[0], 4) > 0 && sight == 0)
			ft_putchar_mod('+', new);
		ft_putstr_mod(str, new[7]);
		return (len);
	}
	else if (new[1] > len)
		return (float_wight_more(&new, len, str, sight));
	return (0);
}

int				for_out_floats(int **s, long double d, char *c, int read)
{
	int		*new;
	int		after_p;

	after_p = 0;
	new = *s;
	d += 0.5;
	c = ft_ftoa(&new, d, after_p, read);
	return (out_zero_float(&new, c, read));
}

static int		out_floats(int **s, long double d, int len)
{
	int		read;
	char	*c;
	int		*new;

	c = NULL;
	read = 0;
	new = *s;
	if (d < 0)
	{
		d = d * -1;
		read = 1;
	}
	if (new[2] == -1)
		new[2] = 6;
	if (new[2] == -3 || new[2] == -2)
		for_out_floats(&new, d, c, read);
	else if (new[2] > 0)
	{
		c = ft_ftoa(&new, d, new[2], read);
		len = out_non_zero(&new, c, read);
	}
	return (len);
}

int				work_with_floats(int **s, va_list ap, int read)
{
	long double		d;
	int				*s1;

	s1 = *s;
	if (s1[3] == 3)
		d = va_arg(ap, long double);
	else
		d = va_arg(ap, double);
	read = out_floats(&s1, d, 0);
	return (read);
}
