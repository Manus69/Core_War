#include "function_prototypes.h"


static void print_argument(t_token *token)
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
	ft_printf("argument_type: %s\n", argumnet_type);
}

static void print_type(t_token *token)
{
	char *type;

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
	else if (token->type == operation)
		type = "operation";
	else if (token->type == argument)
		type = "argument";
	else if (token->type == new_line)
		type = "new_line";
	else if (token->type == comma)
		type = "comma";
	ft_printf("Token at %p\nString: %s\n", token, token->type == new_line ? "\\n" : token->string);
	ft_printf("type: %s\n", type);
}

void		display_token(t_token *token)
{
	if (!token)
	{
		ft_printf("Null token\n");
		ft_printf("---------------\n");
		return ;
	}
	print_type(token);
	if (token->type == argument)
		print_argument(token);
	ft_printf("size: %d\n", token->size);
	ft_printf("distance: %d\n", token->distance);
	ft_printf("---------------\n");
}