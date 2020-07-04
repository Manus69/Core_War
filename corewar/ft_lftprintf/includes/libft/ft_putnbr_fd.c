/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 16:39:12 by selly             #+#    #+#             */
/*   Updated: 2019/10/10 15:17:44 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		factor(int c)
{
	int		i;

	i = 1;
	while (--c)
		i *= 10;
	return (i);
}

static int		symbols(int nb)
{
	int		i;

	i = 0;
	if (nb < 0)
	{
		i++;
		nb = -nb;
	}
	while (nb != 0)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

static int		test_number(int nb, int fd)
{
	if (nb == 0)
	{
		ft_putchar_fd('0', fd);
		return (1);
	}
	if (nb == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return (1);
	}
	if (nb == 2147483647)
	{
		ft_putstr_fd("2147483647", fd);
		return (1);
	}
	return (0);
}

void			ft_putnbr_fd(int nb, int fd)
{
	int		chars;
	int		place;

	chars = symbols(nb);
	if (test_number(nb, fd))
		return ;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		chars--;
		nb = -nb;
	}
	place = factor(chars);
	if (chars == 1)
		ft_putchar_fd(nb + '0', fd);
	else
		while (chars-- != 0)
		{
			ft_putchar_fd((nb / place + '0'), fd);
			nb = nb % place;
			place = place / 10;
		}
}
