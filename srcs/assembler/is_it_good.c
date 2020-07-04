/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_good.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:20:06 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 17:20:35 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"
#include "tables.h"

int	is_command(char *string)
{
	return (is_string_in_array(string, (const char **)g_command_names));
}

int	is_command_name(char *string)
{
	if (ft_strcmp(string, g_command_names[0]) == 0)
		return (1);
	return (0);
}

int	is_command_comment(char *string)
{
	if (ft_strcmp(string, g_command_names[1]) == 0)
		return (1);
	return (0);
}

int	is_string(char *string)
{
	int length;

	length = ft_strlen(string);
	if (string[0] == '"')
	{
		if (string[length - 1] == '"')
			return (1);
	}
	return (0);
}
