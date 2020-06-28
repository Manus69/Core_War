/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:23:54 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 15:36:17 by gemerald         ###   ########.fr       */
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

void		classify_token(t_token *current_token, t_token *previous_token)
{
	if (!current_token || !current_token->string)
		return ;
	else if (previous_token == NULL)
		classify_after_null(current_token);
	else if (previous_token->type == new_line)
		classify_after_new_line(current_token);
	else if (previous_token->type == command_name &&
			is_string(current_token->string))
		current_token->type = champ_name;
	else if (previous_token->type == command_comment &&
			is_string(current_token->string))
		current_token->type = champ_comment;
	else if (previous_token->type == label)
		classify_after_label(current_token);
	else if (previous_token->type == operation)
		classify_after_operation(current_token);
	else if (previous_token->type == argument)
		classify_after_argument(current_token);
	else if (previous_token->type == comma &&
			check_argument_token(current_token))
		return ;
	else if (previous_token->type == champ_name &&
			is_new_line(current_token->string))
		current_token->type = new_line;
	else if (previous_token->type == champ_comment &&
			is_new_line(current_token->string))
		current_token->type = new_line;
}
