/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_aggravation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 18:08:24 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/07/03 17:46:56 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		translate_operation(t_container *container,
t_generic_list *current_token, t_generic_list **last_element)
{
	t_generic_list	*token_translation;

	compare_arg_counts(current_token, container);
	if (container->error_status)
		return ;
	token_translation = encode_operation((t_token *)current_token->stuff);
	container->translation->exec_code =
	concatenate_lists(container->translation->exec_code,
			token_translation, *last_element);
	*last_element = token_translation;
	if (g_op_tab[get_operation_name((t_token *)current_token->
				stuff)].arg_code_flag)
	{
		token_translation = encode_type(current_token);
		container->translation->exec_code =
		concatenate_lists(container->translation->exec_code,
				token_translation, *last_element);
		*last_element = token_translation;
	}
}

static void		translate_argument(t_container *container,
	t_flag *flag, t_token *previous_operation, t_generic_list **last_element)
{
	t_generic_list *token_translation;
	t_generic_list *current_token;

	current_token = container->current;
	compare_arg_type(previous_operation, (t_token *)current_token->stuff,
			container, flag);
	token_translation = encode_argument(current_token,
			container->tokens, container);
	container->translation->exec_code = concatenate_lists(container->
			translation->exec_code, token_translation, *last_element);
	*last_element = token_translation;
}

t_generic_list	*translate_tokens(t_container *container, t_flag *has_flag)
{
	t_generic_list	*current;
	t_generic_list	*last_element;
	t_token			*prev_oper;

	last_element = NULL;
	prev_oper = NULL;
	current = container->tokens;
	while (current && !(container->error_status & (E_ARG_COUNT | E_ARG_TYPE)))
	{
		if (((t_token *)current->stuff)->type == champ_name)
			container->translation->champ_name =
					translate_champ_name(current, container);
		else if (((t_token *)current->stuff)->type == champ_comment)
			container->translation->champ_comment =
					translate_champ_comment(current, container);
		else if (((t_token *)current->stuff)->type == operation
				&& (prev_oper = (t_token *)current->stuff))
			translate_operation(container, current, &last_element);
		else if (((t_token *)current->stuff)->type == argument
				&& (container->current = current))
			translate_argument(container, has_flag, prev_oper, &last_element);
		current = current->next;
	}
	return (concatenate_translation(container->translation));
}
