/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:22:37 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 17:24:07 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

static void	measure_arg_size(t_token *token,
		enum e_operation_name operation_type)
{
	if (token->argument_type == registry)
		token->size = REGISTRY_NAME_SIZE;
	else if (token->argument_type == direct)
		token->size = g_op_tab[operation_type].size_t_dir ?
			DIRECT_ADDRESS_SIZE : DIRECT_VALUE_SIZE;
	else if (token->argument_type == indirect)
		token->size = INDIRECT_VALUE_SIZE;
}

void		measure_token_size(t_generic_list *tokens)
{
	enum e_operation_name	operation_type;
	t_generic_list			*current_token;
	t_token					*token;

	current_token = tokens;
	operation_type = dummy_operation;
	while (current_token)
	{
		token = ((t_token *)current_token->stuff);
		if (token->type == champ_name || token->type == champ_comment)
			token->size = ft_strlen(token->string) - 2;
		else if (token->type == operation)
		{
			operation_type = get_operation_name(token);
			if (g_op_tab[operation_type].arg_code_flag == 1)
				token->size = 2;
			else
				token->size = 1;
		}
		else if (token->type == argument)
			measure_arg_size(token, operation_type);
		current_token = current_token->next;
	}
}
