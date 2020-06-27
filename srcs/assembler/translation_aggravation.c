/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_aggravation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 18:08:24 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/06/27 18:08:31 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		translate_operation(t_container *container,
t_generic_list *current_token, t_generic_list **last_element)
{
	t_token			*previous_operation;
	t_generic_list	*token_translation;

	compare_arg_counts(current_token, container);
	previous_operation = (t_token *)current_token->stuff;
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

t_generic_list	*translate_tokens(t_container *cntner, t_flag *has_flag)
{
	t_generic_list	*cur_tok;
	t_generic_list	*last_element;
	t_token			*prev_oper;

	last_element = NULL;
	prev_oper = NULL;
	cur_tok = cntner->tokens;
	while (cur_tok)
	{
		if (((t_token *)cur_tok->stuff)->type == champ_name)
			cntner->translation->champ_name =
					translate_champ_name(cur_tok, cntner);
		else if (((t_token *)cur_tok->stuff)->type == champ_comment)
			cntner->translation->champ_comment =
					translate_champ_comment(cur_tok, cntner);
		else if (((t_token *)cur_tok->stuff)->type == operation
				&& (prev_oper = (t_token *)cur_tok->stuff))
			translate_operation(cntner, cur_tok, &last_element);
		else if (((t_token *)cur_tok->stuff)->type == argument
				&& (cntner->current = cur_tok))
			translate_argument(cntner, has_flag, prev_oper, &last_element);
		cur_tok = cur_tok->next;
	}
	return (concatenate_translation(cntner->translation));
}
