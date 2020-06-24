/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_it_fun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 23:39:03 by lcaesar           #+#    #+#             */
/*   Updated: 2020/06/23 23:39:45 by lcaesar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int     is_quotation_mark(char *string)
{
	return (check_symbol(string, '"'));
}

int     is_comment_character(char *string)
{
	return (check_symbol(string, COMMENT_CHAR) || check_symbol(string, COMMENT_CHAR_2));
}

int     is_new_line(char *string)
{
	return (check_symbol(string, '\n'));
}

int     is_argument_separator(char *string)
{
	return (check_symbol(string, SEPARATOR_CHAR));
}

int     is_operation(char *string)
{
   return (is_string_in_array(string, g_operation_names));
}