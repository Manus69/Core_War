/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_vexation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnarwhal <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:56:56 by mnarwhal          #+#    #+#             */
/*   Updated: 2020/07/04 20:44:28 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

void	check_current_arg_type(t_container *container,
t_token *previous_operation, t_token *current_token, int arg_index)
{
	int						arg_count;
	enum e_operation_name	operation;

	operation = get_operation_name(previous_operation);
	arg_count = g_op_tab[operation].arg_count;
	if (arg_index >= arg_count)
		return ;
	if (!(current_token->argument_type &
		g_op_tab[operation].arg_type[arg_index]))
		container->error_status |= E_ARG_TYPE;
}

int		get_arg_count_check_type(t_container *container, t_generic_list *token)
{
	t_generic_list	*current_token;
	t_token			*previous_operation;
	int				arg_count;

	arg_count = 0;
	previous_operation = (t_token *)token->stuff;
	current_token = token->next;
	while (1)
	{
		if (!current_token)
			return (arg_count);
		if (((t_token *)current_token->stuff)->type == comma)
			current_token = current_token->next;
		else if (((t_token *)current_token->stuff)->type == argument)
		{
			check_current_arg_type(container, previous_operation,
			((t_token *)current_token->stuff), arg_count);
			arg_count++;
			current_token = current_token->next;
		}
		else
			break ;
	}
	return (arg_count);
}

void	compare_arg_counts(t_generic_list *token, t_container *container)
{
	t_token					*token_cast;
	enum e_operation_name	operation_name;
	int						arg_count;

	token_cast = (t_token *)token->stuff;
	operation_name = get_operation_name(token_cast);
	arg_count = get_arg_count_check_type(container, token);
	if (g_op_tab[operation_name].arg_count != arg_count)
		container->error_status |= E_ARG_COUNT;
}

int		get_operation_code(t_token *token)
{
	int						value;
	int						n;
	enum e_operation_name	operation_name;

	operation_name = get_operation_name(token);
	value = 0;
	n = 0;
	while (n < g_op_tab[operation_name].arg_count)
	{
		value = (value | g_op_tab[operation_name].arg_type[n]);
		n++;
	}
	return (value);
}

void	compare_arg_type(t_token *previous_operation,
t_token *current_token, t_container *container, t_flag *flag)
{
	unsigned int table_value;

	if (!previous_operation)
	{
		flag = free_structure(flag);
		invoke_error(UNEXPECTED_ERROR, NULL, NULL, container);
	}
	table_value = get_operation_code(previous_operation);
	if (table_value != (table_value | current_token->argument_type))
	{
		flag = free_structure(flag);
		container->error_status |= E_ARG_TYPE;
	}
}
