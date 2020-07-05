/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 20:42:25 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/05 14:37:34 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"
#include "tables.h"

static void	display_syntax_errors(short status_code)
{
	short				number;
	const char *const	*message;

	number = 1;
	message = g_syntax_errors;
	while (*message)
	{
		if (status_code & number)
			ft_putstr_fd(*message, STDERR_FILENO);
		number = number << 1;
		message++;
	}
}

static void	classification_check(t_container *container, t_token *current_token)
{
	short status_code;

	status_code = 0;
	if (!current_token)
		invoke_error(COMPILATION_TERMINATED, NULL,
				"\nEmpty token list;\n", container);
	if (current_token->type != new_line)
		status_code |= S_NEW_LINE;
	if ((!(container->list_status >> 1)) & 1)
		status_code |= S_NAME;
	if (!(container->list_status & 1))
		status_code |= S_COMMENT;
	if (status_code)
	{
		display_syntax_errors(status_code);
		invoke_error(COMPILATION_TERMINATED, NULL, NULL, container);
	}
}

static void	class_helper(t_token **current_token, t_token **previous_token,
		t_generic_list **current_item, t_container **container)
{
	if (!((*current_item)->stuff))
		invoke_error("Current token is bricked!\n previous token:",
				(*previous_token), NULL, (*container));
	(*current_token) = (*current_item)->stuff;
	classify_token((*current_token), (*previous_token));
	if ((*current_token)->type == unknown)
		invoke_error(CLASSIFICATION_ERROR_MESSAGE,
				(*current_token), NULL, (*container));
}

void		classify_all_tokens(t_container *container)
{
	t_token			*current_token;
	t_token			*previous_token;
	t_generic_list	*current_item;

	previous_token = NULL;
	current_token = NULL;
	current_item = container->tokens;
	while (current_item)
	{
		class_helper(&current_token, &previous_token,
				&current_item, &container);
		if (current_token->type == label)
			container->labels = add_to_list(container->labels, current_token);
		else if (current_token->type == command_name)
			set_status(container, current_token);
		else if (current_token->type == command_comment)
			set_status(container, current_token);
		current_item = current_item->next;
		previous_token = current_token;
	}
	classification_check(container, current_token);
}
