#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"

t_token *new_token(char *string, enum e_token_type type)
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

t_token *copy_token(t_token *token)
{
    t_token *token_copy;

    token_copy = new_token(token->string, token->type);
    token_copy->argument_type = token->argument_type;
    token_copy->distance = token->distance;
    token_copy->size = token->size;

    return (token_copy);
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

void destroy_token_mk2(void *pp_token)
{
    char **pp_string;
    t_token **pp_token_cast;

    if (!pp_token)
        return ;
    pp_token_cast = (t_token **)pp_token;
    pp_string = &(*pp_token_cast)->string;
    if ((*pp_token_cast)->type != null)
        free((*pp_token_cast)->string);
    *pp_string = NULL;
    free(*pp_token_cast);
    *pp_token_cast = NULL;
}

void destroy_token_dumb(void *token)
{
    t_token *token_cast;

    if (!token)
        return ;
    token_cast = (t_token *)token;
    if (token_cast->type != null)
        free(((t_token *)token)->string);
    free(token);
}