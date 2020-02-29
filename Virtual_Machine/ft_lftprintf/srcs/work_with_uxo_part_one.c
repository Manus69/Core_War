#include "printf.h"

static int		if_minus_in_fl_one(int **s, int z)
{
	int		*new;

	new = *s;
	if (new[4] == 9)
		ft_putstr_mod("0X", new[7]);
	else
		ft_putstr_mod("0x", new[7]);
	return (z + 2);
}

static int		if_minus_in_fl_two(int z, int *n)
{
	ft_putchar_mod('0', n);
	return (z + 1);
}

int			if_minus_in_flag_on(int **s, unsigned long d, int count, int base)
{
	int		*n;
	int		z;
	int		flag;

	n = *s;
	flag = (n[4] == 9 ? 1 : 0);
	z = n[2] > count ? n[2] : count;
	if (f_f(n[0], 1) != 0 && d != 0 && n[4] != 6)
		z = if_minus_in_fl_one(&n, z);
	else if (f_f(n[0], 1) != 0 && d != 0 && n[4] == 6)
		z = if_minus_in_fl_two(z, n);
	if (n[4] == 6 && n[2] > count && f_f(n[0], 1) != 0 && n[1] > n[2]
		&& f_f(n[0], 3) != 0 && d != 0)
	{
		count = count + 1;
		z = z - 1;
	}
	while (n[2]-- > count)
		ft_putchar_mod('0', n);
	ft_putnbr_base_p(d, base, flag, n);
	while (n[1]-- > z)
		ft_putchar_mod(' ', n);
	return (n[1]);
}

static int		if_minus_off_part_three(int **s, int back_int)
{
	int		*new;

	new = *s;
	if (new[4] == 6 && new[2] != -3)
	{
		if (new[2] == -2 && f_f(new[0], 1) <= 0)
		{
			ft_putchar_mod(' ', new);
			return (back_int);
		}
		ft_putchar_mod('0', new);
		return (back_int);
	}
	else
		ft_putchar_mod(' ', new);
	return (back_int);
}

void		write_o_x_o(int **s)
{
	int		*new;

	new = *s;
	if (new[4] == 6)
		ft_putstr_mod(" 0", new[7]);
	else
	{
		if (new[4] == 9)
			ft_putstr_mod("0X", new[7]);
		else
			ft_putstr_mod("0x", new[7]);
	}
}

int			if_minus_in_flag_off(int **s, unsigned long d, int count, int base)
{
	int		*n;
	int		back_int;
	int		flag;

	n = *s;
	flag = (n[4] == 9 ? 1 : 0);
	back_int = n[1];
	if (f_f(n[0], 2) != 0 && f_f(n[0], 1) != 0)
		if_minus_off_part_one(&n, d, count);
	else if (f_f(n[0], 2) != 0 && f_f(n[0], 1) <= 0)
		while (n[1]-- > count)
			ft_putchar_mod('0', n);
	else
	{
		if_minus_off_part_two(&n, d, count);
		if (d == 0 && n[2] == -2)
			return (if_minus_off_part_three(&n, back_int));
	}
	if ((f_f(n[0], 1) != 0 && d != 0 && f_f(n[0], 2) == 0) || n[4] == 3)
		write_o_x_o(&n);
	((n[2] == -3 && f_f(n[0], 1) <= 0) || (n[2] == -3 && (n[4] == 8 ||
		n[4] == 9))) ? ft_putchar_mod(' ', n) : ft_putnbr_base_p(d, base, flag, n);
	return (back_int);
}

void		if_wight_more_acur_out_one(int **s, int count)
{
	int		*new;

	new = *s;
	if (new[4] == 6 && new[2] < count)
		ft_putchar_mod('0', new);
	else if (new[4] == 6)
		ft_putchar_mod(' ', new);
	else if (new[4] != 6)
	{
		if (new[4] == 9)
			ft_putstr_mod("0X", new[7]);
		else
			ft_putstr_mod("0x", new[7]);
	}
}

void		if_wight_more_acur_two(int **s, unsigned long d, int z, int count)
{
	int		*new;

	new = *s;
	if (f_f(new[0], 1) > 0 && d != 0 && new[4] == 6)
		z = z + 1;
	else if (f_f(new[0], 1) > 0 && d != 0 && new[4] != 6)
		z = z + 2;
	while (new[1]-- > z)
		ft_putchar_mod(' ', new);
	if (f_f(new[0], 1) > 0 && d != 0)
		if_wight_more_acur_out_one(&new, count);
	while (new[2]-- > count)
		ft_putchar_mod('0', new);
}

int			if_wight_more_acur(int **s, unsigned long d, int count, int base)
{
	int		z;
	int		*new;
	int		back_int;
	int		flag;

	new = *s;
	flag = (new[4] == 9 ? 1 : 0);
	z = new[2] > count ? new[2] : count;
	back_int = new[1];
	if (f_f(new[0], 3) == 0)
	{
		if_wight_more_acur_two(&new, d, z, count);
		ft_putnbr_base_p(d, base, flag, new);
		return (back_int);
	}
	else if (f_f(new[0], 3) != 0)
		if_minus_in_flag_on(&new, d, count, base);
	return (back_int);
}

int			if_flags_more_d_two(int **s, unsigned long d, int base, int count)
{
	int		*new;
	int		back_int;
	int		flag;

	new = *s;
	back_int = new[2];
	flag = (new[4] == 9 ? 1 : 0);
	if (f_f(new[0], 1) != 0 && d != 0 && new[4] != 6)
	{
		if (new[4] == 3)
			back_int = back_int + 2;
		(new[4] == 9) ? ft_putstr_mod("0X", new[7]) : ft_putstr_mod("0x", new[7]);
	}
	while (new[2]-- > count)
		ft_putchar_mod('0', new);
	ft_putnbr_base_p(d, base, flag, new);
	return (back_int);
}

int			if_flags_more_d(int **s, unsigned long d, int count, int base)
{
	int		*new;
	int		back_int;
	int		flag;

	new = *s;
	flag = (new[4] == 9 ? 1 : 0);
	back_int = new[2];
	if (new[2] > new[1])
		return (if_flags_more_d_two(&new, d, base, count));
	else if (new[1] >= new[2])
		return (if_wight_more_acur(&new, d, count, base));
	else if (new[2] > count)
	{
		while (new[2]-- > count)
			ft_putchar_mod('0', new);
		ft_putnbr_base_p(d, base, flag, new);
		return (back_int);
	}
	return (count);
}

int			true_score_two(int **s, int count)
{
	int		*new;

	new = *s;
	if (new[4] == 6)
		count +=ft_putchar_mod('0',new);
	else
	{
		if (new[4] == 9)
			count += ft_putstr_mod("0X", new[7]);
		else
			count += ft_putstr_mod("0x", new[7]);
	}
	return (count);
}

int			true_score(int **s, unsigned long d, int count, int base)
{
	int		*new;
	int		flag;

	new = *s;
	flag = (new[4] == 9 ? 1 : 0);
	if ((f_f(new[0], 1) != 0 && d != 0) || new[4] == 3)
		count = true_score_two(&new, count);
	else if (new[2] == -2 && d == 0 && new[4] != 6)
		return (0);
	else if (new[2] == -3 && new[4] == 8)
		return (0);
	if (new[2] != -3 || new[4] == 6)
		ft_putnbr_base_p(d, base, flag, new);
	return (count);
}

