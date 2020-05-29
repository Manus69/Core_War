#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"

t_token *new_token(char *string, enum e_token_type type)
{
    t_token *token;

    token = mallokill(sizeof(t_token));
    token->string = string;
    if (type == 0)
        token->type = unknown;
    else
        token->type = type;
    token->argument_type = not_applicable;
    token->size = 0;
    token->distance = -1;
    return (token);
}

void destroy_token(t_token **token)
{
    if (!token)
        return ;
    if (!*token)
        return ;
    if ((*token)->type != null)
        free((*token)->string);
    free(*token);
    *token = NULL;
}

