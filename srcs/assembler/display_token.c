/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:17:09 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/03 17:15:20 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	print_argument(t_token *token, int fd)
{
	char *argumnet_type;

	if (token->argument_type == registry)
		argumnet_type = "registry";
	else if (token->argument_type == direct)
		argumnet_type = "direct";
	else if (token->argument_type == indirect)
		argumnet_type = "indirect";
	else
		argumnet_type = "not_applicable";
	ft_putstr_fd("argument_type: ", fd);
	ft_putstr_fd(argumnet_type, fd);
	ft_putstr_fd("\n", fd);
}

static void	print_type_helper(char **type, t_token *token)
{
	if (token->type == operation)
		(*type) = "operation";
	else if (token->type == argument)
		(*type) = "argument";
	else if (token->type == new_line)
		(*type) = "new_line";
	else if (token->type == comma)
		(*type) = "comma";
}

static void	print_type(t_token *token, int fd)
{
	char *type;

	type = NULL;
	if (token->type == null)
		type = "null";
	else if (token->type == unknown)
		type = "unknown";
	else if (token->type == command_name)
		type = "command_name";
	else if (token->type == command_comment)
		type = "command_comment";
	else if (token->type == champ_name)
		type = "champ_name";
	else if (token->type == champ_comment)
		type = "champ_comment";
	else if (token->type == label)
		type = "label";
	else
		print_type_helper(&type, token);
	ft_putstr_fd("Token string: ", fd);
	ft_putstr_fd(token->type == new_line ? "\\n" : token->string, fd);
	ft_putstr_fd("\ntype: ", fd);
	ft_putstr_fd(type, fd);
	ft_putstr_fd("\n", fd);
}

void		display_token(t_token *token, int fd)
{
	if (!token)
	{
		ft_putstr_fd("Null token\n---------------\n", fd);
		return ;
	}
	print_type(token, fd);
	if (token->type == argument)
		print_argument(token, fd);
	if (fd == STDOUT_FILENO)
	{
		ft_printf("size: %d\n", token->size);
		ft_printf("distance: %d\n", token->distance);
	}
	ft_putstr_fd("---------------\n", fd);
}
