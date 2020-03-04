#include "function_prototypes.h"
#include "ft_printf.h"

void display_token(t_token *token)
{
    char *type;

    if (!token)
    {
        ft_printf("Null token\n");
        ft_printf("---------------\n");
        return ;
    }
    type = "unknown";
    if (token->type == command)
        type = "command";
    else if (token->type == string)
        type = "string";
    else if (token->type == label)
        type = "label";
    else if (token->type == operation)
        type = "operation";
    else if (token->type == argument)
        type = "argument";
    else if (token->type == comment)
        type = "comment";
    else if (token->type == new_line)
        type = "new_line";
    ft_printf("Token at %p\nString: %s\n", token, token->string);
    ft_printf("type: %s\n", type);
    ft_printf("---------------\n");
}

void display_all_tokens(t_generic_list *tokens)
{
    t_generic_list *current;

    current = tokens;
    while (current != NULL)
    {
        display_token((t_token *)current->stuff);
        current = current->next;
    }
}

void display_classification_error_message(t_token *token, int verbose)
{
    if (verbose)
    {
        ft_printf(CLASSIFICATION_ERROR_MESSAGE);
        display_token(token);
    }
    else
    {
        ft_printf(GENERIC_ERROR_MESSAGE);
    }
    exit(1);
}