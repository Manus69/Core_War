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
    invoke_error("get next typed token is broken\nlast token:", token_cast, NULL); //change the message later;
    return (NULL);
}

t_transcription_parameters *get_transcription_parameters(t_generic_list *tokens)
{
    t_transcription_parameters *parameters;
    t_generic_list *current_token;
    t_token *token_cast;
    int distance;

    parameters = mallokill(sizeof(t_transcription_parameters));

    //champ name
    current_token = get_next_typed_token(tokens, string);
    if (!current_token)
        invoke_error("cant get transcription parameters\n", NULL, NULL); //get the right message;
    token_cast = (t_token *)current_token->stuff;
    parameters->name_size = ft_strlen(((t_token *)current_token->stuff)->string) - 2;
    if (parameters->name_size > PROG_NAME_LENGTH)
        invoke_error("champ name is too big", NULL, NULL); //msg
    
    //getting champ comment
    current_token = get_next_typed_token(current_token, string);
    if (!current_token)
        invoke_error("cant get transcription parameters 2\n", NULL, NULL); //msg
    token_cast = (t_token *)current_token->stuff;
    parameters->comment_size = ft_strlen(((t_token *)current_token->stuff)->string) - 2;
    if (parameters->comment_size > COMMENT_LENGTH)
        invoke_error("champ comment is too long", NULL, NULL); //message

    //exec code size
    current_token = get_last_element(tokens);
    if (!current_token)
        invoke_error("cant get transcription parameters 3\n", NULL, NULL); //msg
    token_cast = (t_token *)current_token->stuff;
    parameters->exec_code_size = ((t_token *)current_token->stuff)->distance -
    parameters->name_size - parameters->comment_size;
    if (parameters->exec_code_size > CHAMP_MAX_SIZE)
        invoke_error("champ code is too long\n", token_cast, NULL);
    return (parameters);
}