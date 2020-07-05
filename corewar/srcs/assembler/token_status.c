/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 18:04:22 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 18:04:43 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

enum e_status_code	get_status_code(t_token *token)
{
	if (token->type == command_name)
		return (name_code);
	if (token->type == command_comment)
		return (comment_code);
	return (invoke_error(UNEXPECTED_ERROR, token, NULL, NULL));
}

void				set_status(t_container *container, t_token *token)
{
	short				shifted_number;
	enum e_status_code	status_code;

	status_code = get_status_code(token);
	shifted_number = (1 << status_code);
	if (container->list_status & shifted_number)
		invoke_error("token duplication\n", token, NULL, container);
	container->list_status = (container->list_status | shifted_number);
}
