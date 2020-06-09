#include "function_prototypes.h"
#include "operation_table.h"
#include "constants.h"

int		get_arg_count(t_generic_list *token)
{
	t_generic_list	*current_token;
	t_token			*current_token_cast;
	int				arg_count;

	arg_count = 0;
	current_token = token->next;

	while (1)
	{
		if (!current_token)
			return (arg_count);
		current_token_cast = (t_token *)current_token->stuff;
		if (current_token_cast->type == comma)
			current_token = current_token->next;
		else if (current_token_cast->type == argument)
		{
			arg_count ++;
			current_token = current_token->next;
		}
		else
			break ;
	}
	return (arg_count);
}

void compare_arg_counts(t_generic_list *token, t_container *container)
{
	t_token					*token_cast;
	enum e_operation_name	operation_name;
	int						arg_count;

	token_cast = (t_token *)token->stuff;
	operation_name = get_operation_name(token_cast);
	arg_count = get_arg_count(token);
	if (op_tab[operation_name].arg_count != arg_count)
		invoke_error("wrong number of arguments for token\n", token_cast, NULL, container); //msg
}

int		get_operation_code(t_token *token)
{
	int						value;
	int						n;
	enum e_operation_name	operation_name;

	operation_name = get_operation_name(token);
	value = 0;
	n = 0;
	while (n < op_tab[operation_name].arg_count)
	{
		value = (value | op_tab[operation_name].arg_type[n]);
		n ++;
	}
	return (value);
}

void	compare_arg_type(t_token *previous_operation,
t_token *current_token, t_container *container)
{
	unsigned int table_value;

	if (!previous_operation)
		invoke_error(UNEXPECTED_ERROR, NULL, NULL, container);
	table_value = get_operation_code(previous_operation);
	if (table_value != (table_value | current_token->argument_type))
		invoke_error ("argument type mismatch\n", previous_operation, NULL, container); //msg
}
