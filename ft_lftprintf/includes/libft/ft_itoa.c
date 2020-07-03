/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:03:36 by selly             #+#    #+#             */
/*   Updated: 2019/10/30 14:23:48 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_delitel(int n)
{
	int		result;

	result = 1;
	while (n)
	{
		result *= 10;
		n--;
	}
	return (result);
}

static int			ft_chars(long n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char			*ft_getarray(char *ar, int n, int chars, int a)
{
	if (n < 0)
	{
		chars--;
		ar[a++] = '-';
		n = -n;
	}
	while (chars--)
	{
		ar[a] = n / ft_delitel(chars) + '0';
		a++;
		n %= ft_delitel(chars);
	}
	ar[a] = '\0';
	return (ar);
}

static char			*ft_max(int c)
{
	char	*new;

	if (c == 0)
	{
		new = ft_strnew(1);
		*new = '0';
		new[1] = '\0';
	}
	else
	{
		new = ft_strnew(11);
		new[0] = '-';
		new[1] = '2';
		new = ft_getarray(new, 147483648, 9, 2);
		return (new);
	}
	return (new);
}

char				*ft_itoa(int n)
{
	int		chars;
	char	*new;

	if (n == -2147483648 || n == 0)
		new = ft_max(n);
	else
	{
		chars = ft_chars(n);
		if (!(new = ft_strnew(chars)))
			return (NULL);
		new = ft_getarray(new, n, chars, 0);
	}
	return (new);
}
