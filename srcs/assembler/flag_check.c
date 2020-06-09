#include "asm.h"

#include "asm.h"

int 	has_char(char *str, char find)
{
	int result;

	result = 0;
	while (*str)
	{
		if (*str == find)
			return (SUCCESS);
		str++;
	}
	return (result);
}

int 	check_new_name(char		*name)
{
	int 	i;
	char 	*alpha = "abcdefghigklmnopqrstuvwxyz_";
	char 	*not_first = "ABCDEFGHIGKLMNOPQRSTUVWXYZ1234567890";

	i = 0;
	while (name[i] != '\0')
	{
		if (i == 0)
		{
			if (!has_char(alpha, name[i]))
				return(ERR_READ);
		}
		else
		{
			if (!has_char(alpha, name[i]) && !has_char(not_first, name[i]))
				return(ERR_READ);
		}
		i++;
	}
	return (SUCCESS);
}

char 	*get_new_name(char *s, int len)
{
	int 	i;
	char 	*new;
	char 	*end = ".cor";

	len += 4;
	i = 0;
	if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
		ft_putstr_fd("Malloc error", 2);
	while (i < len)
	{
		if (*s)
		{
			new[i] = *s;
			s++;
		}
		else
		{
			new[i] = *end;
			end++;
		}
		i++;
	}
	new[len] = '\0';
	return (new);
}


int 	is_flag(char *test, t_flag *has_flag, int *arg_count, char **av)
{
	if (test[0] == '-' && test[1]=='a' && test[2] == '\0') //если флаг -а запоминаем и идем дальше
	{
		(*has_flag).flag_a = 1;
		return (SUCCESS);
	}
	else if (test[0] == '-' && test[1]=='n' && test[2] == '\0') //если флаг -n считываем новое имя файла и идем дальше
	{
		*arg_count += 1;
		if (check_new_name(av[*arg_count]))
		{
			(*has_flag).new_file_name = get_new_name(av[*arg_count], ft_strlen(av[*arg_count]));
			(*has_flag).change_name = 1;
			return (SUCCESS);
		}
		else
			return(ERR_READ);
	}
	else
		return(ERR_READ);
}

t_flag		*free_structure(t_flag	*has_flag)
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
	return (has_flag);
}