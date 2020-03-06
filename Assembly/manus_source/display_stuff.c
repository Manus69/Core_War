#include "function_prototypes.h"
#include "ft_printf.h"

void display_token(t_token *token)
{
    char *type;
    char *argumnet_type;

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
    else if (token->type == opening_quotation_mark)
        type = "opening_quotation_mark";
    else if (token->type == closing_quotation_mark)
        type = "closing_quotation_mark";
    else if (token->type == hashtag)
        type = "hashtag";
    else if (token->type == comma)
        type = "comma";
    ft_printf("Token at %p\nString: %s\n", token, token->type == new_line ? "\\n" : token->string);
    ft_printf("type: %s\n", type);
    if (token->type == argument)
    {
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

void display_byte_strings(t_generic_list *tokens)
{
    t_generic_list *current;

    current = tokens;
    while (current)
    {
        ft_printf("%s ", current->stuff);
        current = current->next;
    }
}