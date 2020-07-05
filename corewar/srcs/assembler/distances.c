/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distances.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:27:45 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/04 20:43:27 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

int		get_absolute_distance_to_the_label(t_token *token,
		char *label_name, t_container *container)
{
	t_generic_list	*current_token;
	char			*substring;
	t_token			*debug_token;

	current_token = container->labels;
	while (current_token)
	{
		debug_token = (t_token *)current_token->stuff;
		substring = ft_strsub(debug_token->string,
		0, ft_strlen(debug_token->string) - 1);
		if (ft_strcmp(substring, label_name) == 0)
		{
			free(substring);
			return (((t_token *)current_token->stuff)->distance -\
					token->distance);
		}
		free(substring);
		current_token = current_token->next;
	}
	container->error_status |= E_LABEL;
	return (0);
}

int		get_distance_to_the_previous_operation(t_token *token,
		t_generic_list *token_list)
{
	t_generic_list	*current_token;
	t_token			*previous_operation;

	current_token = token_list;
	previous_operation = NULL;
	while (current_token)
	{
		if (((t_token *)current_token->stuff)->type == operation)
		{
			if (((t_token *)current_token->stuff)->distance < token->distance)
				previous_operation = ((t_token *)current_token->stuff);
			else
				break ;
		}
		current_token = current_token->next;
	}
	if (!previous_operation)
		return (-1);
	return (token->distance - previous_operation->distance);
}

int		get_distance_to_the_next_operation(t_generic_list *token)
{
	t_generic_list	*current_token;
	int				distance;

	current_token = token;
	distance = -1;
	while (current_token)
	{
		if (((t_token *)current_token->stuff)->type == operation)
		{
			distance = ((t_token *)current_token->stuff)->distance -
			((t_token *)token->stuff)->distance;
			break ;
		}
		current_token = current_token->next;
	}
	return (distance);
}

int		get_distance_to_the_label(t_generic_list *token, char *label_name,
		t_generic_list *tokens, t_container *container)
{
	int		absolute_distance;
	int		distance_to_the_previous_operation;
	t_token	*current_token;

	current_token = ((t_token *)token->stuff);
	absolute_distance = get_absolute_distance_to_the_label(current_token,
	label_name, container);
	distance_to_the_previous_operation =
	get_distance_to_the_previous_operation(current_token, tokens);
	if (distance_to_the_previous_operation < 0)
		invoke_error(UNEXPECTED_ERROR, current_token, NULL, NULL);
	return (absolute_distance + distance_to_the_previous_operation);
}

void	set_global_distance(t_container *container)
{
	int				distance;
	t_generic_list	*current_token;

	current_token = container->tokens;
	distance = 0;
	while (current_token)
	{
		((t_token *)current_token->stuff)->distance = distance;
		distance = distance + ((t_token *)current_token->stuff)->size;
		current_token = current_token->next;
	}
	container->size_of_tokens = distance;
}
