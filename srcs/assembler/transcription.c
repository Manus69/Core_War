/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transcription.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 18:05:18 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 18:11:09 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define UNEXPECTED_QUIT "the programm quit unexpectedly\nlast token:"

t_generic_list	*get_next_typed_token(t_generic_list *tokens,
		enum e_token_type type)
{
	static const char	*message = UNEXPECTED_QUIT;
	t_generic_list		*current_token;
	t_token				*token_cast;

	token_cast = NULL;
	current_token = tokens->next;
	while (current_token)
	{
		token_cast = (t_token *)current_token->stuff;
		if (token_cast->type == type)
			return (current_token);
		current_token = current_token->next;
	}
	invoke_error(message, token_cast, NULL, NULL);
	return (NULL);
}

void			get_name_size(t_generic_list *tokens, t_container *container)
{
	t_generic_list		*current_token;
	t_token				*token_cast;
	static const char	*message = "champ name is too big";

	current_token = get_next_typed_token(tokens, champ_name);
	if (!current_token)
		invoke_error(UNEXPECTED_ERROR, NULL, NULL, container);
	token_cast = (t_token *)current_token->stuff;
	container->parameters->name_size = ft_strlen(token_cast->string) - 2;
	if (container->parameters->name_size > PROG_NAME_LENGTH)
		invoke_error(message, NULL, NULL, container);
}

void			get_comment_size(t_generic_list *tokens, t_container *container)
{
	t_generic_list		*current_token;
	t_token				*token_cast;
	static const char	*message = "champ comment is too long";

	current_token = get_next_typed_token(tokens, champ_comment);
	if (!current_token)
		invoke_error(UNEXPECTED_ERROR, NULL, NULL, container);
	token_cast = (t_token *)current_token->stuff;
	container->parameters->comment_size = ft_strlen(token_cast->string) - 2;
	if (container->parameters->comment_size > COMMENT_LENGTH)
		invoke_error(message, NULL, NULL, container);
}

void			get_transcription_parameters(t_container *container)
{
	static const char *message = "champ code is too long\n";

	get_name_size(container->tokens, container);
	get_comment_size(container->tokens, container);
	container->parameters->exec_code_size = container->size_of_tokens -
	container->parameters->name_size - container->parameters->comment_size;
	if (container->parameters->exec_code_size > CHAMP_MAX_SIZE)
		invoke_error(message, NULL, NULL, container);
}
