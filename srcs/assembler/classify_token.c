/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:23:54 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/03 17:10:29 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_argument_token(t_token *token)
{
	if (is_registry(token->string))
	{
		token->type = argument;
		token->argument_type = registry;
		return (1);
	}
	else if (is_direct(token->string))
	{
		token->type = argument;
		token->argument_type = direct;
		return (1);
	}
	else if (is_indirect(token->string))
	{
		token->type = argument;
		token->argument_type = indirect;
		return (1);
	}
	return (0);
}

void		classify_token(t_token *current, t_token *previous)
{
	if (!current || !current->string)
		return ;
	else if (previous == NULL)
		classify_after_null(current);
	else if (previous->type == new_line)
		classify_after_new_line(current);
	else if (previous->type == command_name && is_string(current->string))
		current->type = champ_name;
	else if (previous->type == command_comment && is_string(current->string))
		current->type = champ_comment;
	else if (previous->type == label)
		classify_after_label(current);
	else if (previous->type == operation)
		classify_after_operation(current);
	else if (previous->type == argument)
		classify_after_argument(current);
	else if (previous->type == comma && check_argument_token(current))
		return ;
	else if (previous->type == champ_name && is_new_line(current->string))
		current->type = new_line;
	else if (previous->type == champ_comment && is_new_line(current->string))
		current->type = new_line;
}
