/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_arguments.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:33:05 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:39:02 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

char			*get_registry_encoding(t_token *token, t_container *container)
{
	char	*registry_encoding;
	char	*value_substring;
	int		registry_value;

	value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1);
	registry_value = ft_atoi(value_substring);
	free(value_substring);
	if (registry_value < 1 || registry_value > REG_NUMBER)
		container->error_status |= E_REG_INDEX;
	registry_encoding = decimal_to_hex_mk2(registry_value, token->size);
	return (registry_encoding);
}

char			*get_number_encoding(t_token *token)
{
	char	*number_encoding;
	char	*value_substring;
	void	*pointer;
	int		number;

	pointer = NULL;
	if (token->string[0] == '-')
		value_substring = token->string;
	else if (is_a_member(DIGITS, token->string[0]))
		value_substring = token->string;
	else
	{
		value_substring = ft_strsub(token->string, 1,
				ft_strlen(token->string) - 1);
		pointer = value_substring;
	}
	number = (int)why_atol(value_substring);
	if (token->size == 2)
		number_encoding = decimal_to_hex_mk2((short)number, token->size);
	else
		number_encoding = decimal_to_hex_mk2(number, token->size);
	free(pointer);
	return (number_encoding);
}

char			*get_label_encoding(t_generic_list *token,
		t_generic_list *tokens, t_container *container)
{
	int		distance;
	char	*label_name;
	t_token	*current_token;
	char	*label_encoding;
	int		index;

	current_token = ((t_token *)token->stuff);
	index = 0;
	while (!is_a_member(LABEL_CHARS, current_token->string[index]))
		index++;
	label_name = ft_strsub(current_token->string,
	index, ft_strlen(current_token->string) - 1);
	distance = get_distance_to_the_label(token, label_name, tokens, container);
	label_encoding = decimal_to_hex_mk2(distance, current_token->size);
	free(label_name);
	return (label_encoding);
}

t_generic_list	*encode_argument(t_generic_list *token,
		t_generic_list *tokens, t_container *container)
{
	t_generic_list	*encoding;
	t_token			*current_token;
	char			*encoding_string;

	encoding_string = NULL;
	current_token = (t_token *)token->stuff;
	if (current_token->argument_type == registry)
		encoding_string = get_registry_encoding(current_token, container);
	else if (current_token->argument_type == direct)
	{
		if (current_token->string[1] == LABEL_CHAR)
			encoding_string = get_label_encoding(token, tokens, container);
		else
			encoding_string = get_number_encoding(current_token);
	}
	else if (current_token->argument_type == indirect)
	{
		if (current_token->string[0] == LABEL_CHAR)
			encoding_string = get_label_encoding(token, tokens, container);
		else
			encoding_string = get_number_encoding(current_token);
	}
	encoding = new_generic_list(encoding_string);
	return (encoding);
}
