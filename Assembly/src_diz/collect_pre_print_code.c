/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_pre_print_code.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:23:42 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:23:58 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		collect_pre_print(t_dsm *src_code)
{
	if (!(src_code->output = ft_strnew(OUTPUT_LEN)))
		return (FAIL);
	src_code->output_position = 0;
	if (!(put_name_comment(src_code)))
		return (FAIL);
	return (SUCCESS);
}
