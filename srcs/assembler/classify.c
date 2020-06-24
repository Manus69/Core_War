/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classify.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 23:25:33 by lcaesar           #+#    #+#             */
/*   Updated: 2020/06/23 23:25:29 by lcaesar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void classification_check(t_container *container, t_token *current_token)
{
	if (current_token->type != new_line)
		invoke_error("no new line at the end of file\n", NULL, NULL, container); //msg
	if ((!(container->status >> 1)) & 1) // было if (!(container->status >> 1) & 1)
		invoke_error("name command is missing\n", NULL, NULL, container);
	if (!(container->status & 1))
		invoke_error("comment command is missing\n", NULL, NULL, container);
}

void		classify_all_tokens(t_container *container)
{
	t_token			*current_token;
	t_token			*previous_token;
	t_generic_list	*current_item;

	previous_token = NULL;
	current_item = container->tokens;
	while (current_item)
	{
		if (!current_item->stuff)
			invoke_error("current token is bricked!\n previous token:", previous_token, NULL, container); //msg
		current_token = current_item->stuff;
		classify_token(current_token, previous_token);
		if (current_token->type == unknown)
			invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL, container);
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