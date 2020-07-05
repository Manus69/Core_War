/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:52:28 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 17:13:27 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		has_char(char *str, char find)
{
	int	result;

	result = 0;
	while (*str)
	{
		if (*str == find)
			return (SUCCESS);
		str++;
	}
	return (result);
}

int		check_new_name(char *name)
{
	int		i;
	char	*alpha;
	char	*not_first;

	i = 0;
	alpha = "abcdefghigklmnopqrstuvwxyz_";
	not_first = "ABCDEFGHIGKLMNOPQRSTUVWXYZ1234567890";
	while (name[i] != '\0')
	{
		if (i == 0)
		{
			if (!has_char(alpha, name[i]))
				return (ERR_READ);
		}
		else
		{
			if (!has_char(alpha, name[i]) && !has_char(not_first, name[i]))
				return (ERR_READ);
		}
		i++;
	}
	return (SUCCESS);
}

char	*get_new_name(char *s, int len, char **av, int i)
{
	int		a;
	char	*new;
	char	*str;

	a = 0;
	str = ".cor .s";
	if (to_translate(av[i + 1]))
		i = 0;
	else if (to_dizasm(av[i + 1]))
		i = 5;
	else
		return (NULL);
	len += i == 0 ? 4 : 2;
	if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
		ft_putstr_fd("Malloc error", 2);
	while (a < len)
	{
		if (*s)
			new[a++] = *(s++);
		else
			new[a++] = str[i++];
	}
	new[len] = '\0';
	return (new);
}

int		is_flag(char *test, t_flag *has_flag, int *arg_count, char **av)
{
	if (test[0] == '-' && test[1] == 'a' && test[2] == '\0')
	{
		(*has_flag).flag_a = 1;
		return (SUCCESS);
	}
	else if (test[0] == '-' && test[1] == 'v' && test[2] == '\0')
	{
		(*has_flag).visible = 1;
		return (SUCCESS);
	}
	else if (test[0] == '-' && test[1] == 'n' && test[2] == '\0')
	{
		*arg_count += 1;
		if (check_new_name(av[*arg_count]))
		{
			(*has_flag).new_file_name = get_new_name(av[*arg_count],
					ft_strlen(av[*arg_count]), av, *arg_count);
			if (!(*has_flag).new_file_name)
				err_usage("Unknown argument or file!", has_flag);
			(*has_flag).change_name = 1;
			return (SUCCESS);
		}
	}
	return (ERR_READ);
}

t_flag	*free_structure(t_flag *has_flag)
{
	if (has_flag)
	{
		if (has_flag->new_file_name)
		{
			free(has_flag->new_file_name);
			has_flag->new_file_name = NULL;
		}
		if (has_flag->file_name)
		{
			free(has_flag->file_name);
			has_flag->file_name = NULL;
		}
	}
	return (has_flag);
}
