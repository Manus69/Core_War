/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_frustration.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:27:27 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/06/27 17:27:31 by mnarwhal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

t_generic_list	*translate_champ_comment(t_generic_list *current_token,
t_container *container)
{
	t_generic_list		*translation;
	t_generic_list		*last_element;
	t_generic_list		*byte_string;

	translation = encode_string((t_token *)current_token->stuff);
	last_element = get_last_element(translation);
	if (container->parameters->comment_size > COMMENT_LENGTH)
		container->error_status |= E_COMMENT_SIZE;
	byte_string = get_null_padding(COMMENT_LENGTH -
			container->parameters->comment_size);
	translation = concatenate_lists(translation, byte_string, last_element);
	last_element = get_last_element(byte_string);
	byte_string = get_null_padding(PADDING_SIZE);
	translation = concatenate_lists(translation, byte_string, last_element);
	return (translation);
}

t_generic_list	*translate_champ_name(t_generic_list *current_token,
t_container *container)
{
	t_generic_list		*translation;
	t_generic_list		*byte_string;
	t_generic_list		*last_element;

	translation = encode_string((t_token *)current_token->stuff);
	last_element = get_last_element(translation);
	if (container->parameters->name_size > PROG_NAME_LENGTH)
		container->error_status |= E_CHAMP_SIZE;
	byte_string = get_null_padding(PROG_NAME_LENGTH -
			container->parameters->name_size);
	translation = concatenate_lists(translation, byte_string, last_element);
	last_element = get_last_element(byte_string);
	byte_string = get_null_padding(PADDING_SIZE);
	translation = concatenate_lists(translation, byte_string, last_element);
	last_element = get_last_element(byte_string);
	byte_string = new_generic_list(decimal_to_hex_mk2(container->parameters->\
				exec_code_size, 4));
	translation = concatenate_lists(translation, byte_string, last_element);
	return (translation);
}
