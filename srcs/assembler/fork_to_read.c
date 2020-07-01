/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_to_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:22:20 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 17:14:20 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_s(char *str, t_flag *has_flag)
{
	if (str)
		here_we_go(str, has_flag);
	has_flag = free_structure(has_flag);
	return (SUCCESS);
}

int		dizasm(char *str, t_flag *has_flag)
{
	t_dsm src_code;

	src_code.input = NULL;
	src_code.current_position = 0;
	src_code.file_name = NULL;
	if (!(src_code.file_len = read_my_binary(str, &src_code.input)))
		return (FAIL);
	if (!take_new_name(&src_code, str))
		return (FAIL);
	if (!validate_binary(&src_code, has_flag))
	{
		if (src_code.file_name)
			free(src_code.file_name);
		return (FAIL);
	}
	return (SUCCESS);
}
