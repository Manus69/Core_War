#include "libft.h"

static int		is_space(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

long				ft_atoi_size_t(char const *s)
{
	long		num;

	num = 0;
	while (is_space(*s))
		s++;
	if (*s == '-')
		return (-1);
	if (*s == '+')
		s++;
	while (*s == '0')
		s++;
	while (*s >= '0' && *s <= '9' && num + 1 > num)
	{
		num = num * 10 + (*s - '0');
		s++;
	}
	if (*s >= '0' && *s <= '9' && num + 1 < num)
		return (-1);
	return (num);
}
