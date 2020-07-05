/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:40:17 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/04 20:41:35 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

t_generic_list	*encode_operation(t_token *token)
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
