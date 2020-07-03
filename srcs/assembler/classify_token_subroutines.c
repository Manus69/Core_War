/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify_token_subroutines.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:11:20 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/03 17:13:15 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	classify_after_null(t_token *current_token)
{
	if (is_command_name(current_token->string))
		current_token->type = command_name;
	else if (is_command_comment(current_token->string))
		current_token->type = command_comment;
	else if (is_new_line(current_token->string))
		current_token->type = new_line;
}

void	classify_after_new_line(t_token *current_token)
{
	if (is_new_line(current_token->string))
		current_token->type = new_line;
	else if (is_label(current_token->string))
		current_token->type = label;
	else if (is_operation(current_token->string))
		current_token->type = operation;
	else if (is_command_name(current_token->string))
		current_token->type = command_name;
	else if (is_command_comment(current_token->string))
		current_token->type = command_comment;
}

void	classify_after_label(t_token *current_token)
{
	if (is_new_line(current_token->string))
		current_token->type = new_line;
	else if (is_operation(current_token->string))
		current_token->type = operation;
}

void	classify_after_argument(t_token *current_token)
{
	if (is_argument_separator(current_token->string))
		current_token->type = comma;
	else if (is_new_line(current_token->string))
		current_token->type = new_line;
}

void	classify_after_operation(t_token *current_token)
{
	if (check_argument_token(current_token))
		;
	else if (is_new_line(current_token->string))
		current_token->type = new_line;
}
