/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 18:02:43 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 18:03:31 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_token	*new_token(char *string, enum e_token_type type)
{
	t_token *token;

	token = mallokill(sizeof(t_token));
	token->string = ft_strdup(string);
	if (type == 0)
		token->type = unknown;
	else
		token->type = type;
	token->argument_type = not_applicable;
	token->size = 0;
	token->distance = -1;
	return (token);
}

t_token	*copy_token(t_token *token)
{
	t_token *token_copy;

	token_copy = new_token(token->string, token->type);
	token_copy->argument_type = token->argument_type;
	token_copy->distance = token->distance;
	token_copy->size = token->size;
	return (token_copy);
}

void	destroy_token_dumb(void *token)
{
	t_token *token_cast;

	if (!token)
		return ;
	token_cast = (t_token *)token;
	if (token_cast->type != null)
		free(((t_token *)token)->string);
	free(token);
}
