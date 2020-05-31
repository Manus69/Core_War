#include "tokens.h"
#include "function_prototypes.h"

t_generic_list *get_next_typed_token(t_generic_list *tokens, enum e_token_type type)
{
    t_generic_list *current_token;
    t_token *token_cast;

    token_cast = NULL;
    current_token = tokens->next;
    while (current_token)
    {
        token_cast = (t_token *)current_token->stuff;
        if (token_cast->type == type)
            return (current_token);
        current_token = current_token->next;
    }
    invoke_error("the programm quit unexpectedly\nlast token:", token_cast, NULL, NULL);
    return (NULL);
}

void get_name_size(t_generic_list *tokens, t_container *container)
{
    t_generic_list *current_token;
    t_token *token_cast;

    current_token = get_next_typed_token(tokens, champ_name);
    if (!current_token)
        invoke_error("cant get transcription parameters\n", NULL, NULL, container); //get the right message;
    token_cast = (t_token *)current_token->stuff;
    container->parameters->name_size = ft_strlen(((t_token *)current_token->stuff)->string) - 2;
    if (container->parameters->name_size > PROG_NAME_LENGTH)
        invoke_error("champ name is too big", NULL, NULL, container); //msg
}

void get_comment_size(t_generic_list *tokens, t_container *container)
{
    t_generic_list *current_token;

    current_token = get_next_typed_token(tokens, champ_comment);
    if (!current_token)
        invoke_error("cant get transcription parameters 2\n", NULL, NULL, container); //msg
    container->parameters->comment_size = ft_strlen(((t_token *)current_token->stuff)->string) - 2;
    if (container->parameters->comment_size > COMMENT_LENGTH)
        invoke_error("champ comment is too long", NULL, NULL, container); //message
}

void get_transcription_parameters(t_container *container)
{
    //champ name
    get_name_size(container->tokens, container);
    
    //getting champ comment
    get_comment_size(container->tokens, container);

    //exec code size
    container->parameters->exec_code_size = container->size_of_tokens -
    container->parameters->name_size - container->parameters->comment_size;
    if (container->parameters->exec_code_size > CHAMP_MAX_SIZE)
        invoke_error("champ code is too long\n", NULL, NULL, container);
}