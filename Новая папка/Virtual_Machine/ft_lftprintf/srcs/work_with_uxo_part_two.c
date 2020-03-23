
#include "printf.h" /////+++++++

int			wight_more_count_one(int **s, int count)
{
	int		*new;

	new = *s;
	if (new[4] == 6)
		count += ft_putchar_mod('0', new);
	else
	{
		if (new[4] == 9)
			count += ft_putstr_mod("0X", new[7]);
		else
			count += ft_putstr_mod("0x", new[7]);
	}
	return (count);
}

int			wight_more_count_three(int **s)
{
	int		*new;

	new = *s;
	if (f_f(new[0], 1) != 0 && new[4] == 6)
	{
		ft_putchar_mod('0', new);
		new[1] = new[1] - 1;
	}
	write_new_one(new[1], new);
	return (new[2]);
}

void		wight_more_last(int **s, unsigned long d, int *count, int base)
{
	int		*new;
	int		flag;

	new = *s;
	flag = (new[4] == 9 ? 1 : 0);
	if (f_f(new[0], 1) != 0 && d != 0)
		*count = wight_more_count_one(&new, *count);
	if ((new[2] == -3 && f_f(new[0], 1) == 0)
		|| (new[2] == -3 && (new[4] == 8 || new[4] == 9)))
		ft_putchar_mod(' ', new);
	else if (new[4] == 3 && d == 0)
	{
		ft_putstr_mod("0x", new[7]);
		ft_putnbr_base_p(d, base, flag, new);
		new[1] = new[1] - 2;
	}
	else
		ft_putnbr_base_p(d, base, flag, new);
	while (new[1]-- > *count)
		ft_putchar_mod(' ', new);
}

int			wight_more_count(int **s, unsigned long d, int count, int base)
{
	int		*new;
	int		int_back;

	new = *s;
	int_back = new[1];
	if (f_f(new[0], 3) == 0)
		return (if_minus_in_flag_off(&new, d, count, base));
	else if (f_f(new[0], 3) != 0)
	{
		if (d == 0 && new[2] == -2)
			return (wight_more_count_three(&new));
		wight_more_last(&new, d, &count, base);
		return (int_back >= count ? int_back : count);
	}
	return (int_back);
}

void		wight_or_acur_three(int **s, int *count, int *c)
{
	int		*new;

	new = *s;
	*c = *c + 2;
	if (new[4] == 6)
	{
		ft_putchar_mod('0', new);
		*count = *count + 1;
		*c = *c - 2;
	}
	else //нужно ли ниже посчитать count?
	{
		if (new[4] == 9)
			ft_putstr_mod("0X", new[7]);
		else
			ft_putstr_mod("0x", new[7]);
	}
}

int			wight_or_acur(int **s, unsigned long d, int count, int base)
{
	int		*new;
	int		c;
	int		flag;

	new = *s;
	flag = (new[4] == 9 ? 1 : 0);
	c = new[2];
	if ((f_f(new[0], 1) != 0 && d != 0)
		|| (new[2] > count && new[4] == 3))
		{
			wight_or_acur_three(&new, &count, &c);
		}
	while (new[2]-- > count)
		ft_putchar_mod('0', new);
	ft_putnbr_base_p(d, base, flag, new);
	return (c);
}

int			wight_or_acur_two(int **s, unsigned long d, int count, int base)
{
	int		*new;
	int		flag;

	new = *s;
	flag = (new[4] == 9 ? 1 : 0);
	if (f_f(new[0], 1) != 0 && d != 0)
	{
		if (new[4] == 6)
			count += ft_putchar_mod('0', new);
		else
		{
			if (new[4] == 9)
				count += ft_putstr_mod("0X", new[7]);
			else
				count += ft_putstr_mod("0x", new[7]);
		}
	}
	ft_putnbr_base_p(d, base, flag, new);
	return (count);
}

int			work_x_o_u(int **s, unsigned long d, int count, int base)
{
	int		*new;

	new = *s;
	if (new[4] == 3)
		new[0] = new[0] * 10 + 1;
	if (new[1] <= count && new[2] <= count)
		return (true_score(&new, d, count, base));
	if ((new[1] > 0 && new[2] <= 0) || (new[2] > 0 && new[1] <= 0))
	{
		if (new[1] > 0 && new[1] > count)
			return (wight_more_count(&new, d, count, base));
		else if (count >= new[1] && count >= new[2])
			return (wight_or_acur_two(&new, d, count, base));
		else if (new[1] == 0 && new[2] > count)
			return (wight_or_acur(&new, d, count, base));
	}
	if (new[1] > count || new[2] > count)
		return (if_flags_more_d(&new, d, count, base));
	return (count);
}
