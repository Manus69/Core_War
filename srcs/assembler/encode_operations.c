/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 23:33:57 by lcaesar           #+#    #+#             */
/*   Updated: 2020/06/23 23:34:10 by lcaesar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_generic_list *encode_operation(t_token *token)
{
	t_generic_list			*encoding;
	enum e_operation_name	operation;
	char					*operation_code;

	operation = dummy_operation + 1;
	while (operation < NUMBER_OF_OPERATIONS)
	{
		if (strcmp(token->string, g_op_tab[operation].op_name) == 0)
			operation_code = decimal_to_hex_mk2(g_op_tab[operation].op_code, 1);
		operation = operation + 1;
	}
	encoding = new_generic_list(operation_code);
	return (encoding);
}
