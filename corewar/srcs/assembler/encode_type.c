/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:46:14 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:48:08 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

enum e_operation_name	get_operation_name(t_token *token)
{
	enum e_operation_name operation;

	operation = dummy_operation + 1;
	while (operation < NUMBER_OF_OPERATIONS)
	{
		if (ft_strcmp(token->string, g_op_tab[operation].op_name) == 0)
			return (operation);
		operation = operation + 1;
	}
	return (dummy_operation);
}

static char				*get_type_byte_code(t_generic_list *argument_list,
		int arg_count)
{
	char			*byte_code;
	char			*byte;
	t_generic_list	*current_token;

	byte_code = ft_strdup("");
	current_token = argument_list;
	while (arg_count)
	{
		if (((t_token *)current_token->stuff)->argument_type == registry)
			byte = ft_strdup("01");
		else if (((t_token *)current_token->stuff)->argument_type == direct)
			byte = ft_strdup("10");
		else if (((t_token *)current_token->stuff)->argument_type == indirect)
			byte = ft_strdup("11");
		else
			byte = NULL;
		if (byte)
		{
			byte_code = join_and_free(byte_code, byte);
			arg_count--;
		}
		current_token = current_token->next;
	}
	return (byte_code);
}

t_generic_list			*encode_type(t_generic_list *token)
{
	enum e_operation_name	operation;
	t_generic_list			*encoding_list_item;
	char					*result;
	void					*pointer;
	unsigned int			pad_size;

	operation = get_operation_name((t_token *)token->stuff);
	token = token->next;
	result = get_type_byte_code(token, g_op_tab[operation].arg_count);
	pointer = result;
	pad_size = (MAX_ARGS_NUMBER - g_op_tab[operation].arg_count) * 2;
	result = pad_with_chars(result, pad_size, '0', 1);
	encoding_list_item =\
			new_generic_list(decimal_to_hex_mk2(binary_to_decimal(result), 1));
	free(pointer);
	free(result);
	return (encoding_list_item);
}
