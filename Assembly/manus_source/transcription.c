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
    return (NULL); //never executed;
}

t_transcription_parameters *get_transcription_parameters(t_generic_list *tokens)
{
    t_transcription_parameters *parameters;
    t_generic_list *current_token;
    t_token *token_cast;
    int distance;

    parameters = mallokill(sizeof(t_transcription_parameters));
    // current_token = get_next_typed_token(tokens, opening_quotation_mark);
    // distance = ((t_token *)current_token->stuff)->distance;
    // current_token = get_next_typed_token(current_token, closing_quotation_mark);
    // parameters->name_size = ((t_token *)current_token->stuff)->distance - distance;
    current_token = get_next_typed_token(tokens, string);
    token_cast = (t_token *)current_token->stuff;
    parameters->name_size = ft_strlen(((t_token *)current_token->stuff)->string) - 2;
    if (!parameters->name_size)
        invoke_error("cant get transcription parameters\n", token_cast, NULL); //get the right message;
    // current_token = get_next_typed_token(current_token, opening_quotation_mark);
    // distance = ((t_token *)current_token->stuff)->distance;
    // current_token = get_next_typed_token(current_token, closing_quotation_mark);
    // parameters->comment_size = ((t_token *)current_token->stuff)->distance - distance;
    current_token = get_next_typed_token(current_token, string);
    token_cast = (t_token *)current_token->stuff;
    if (!current_token)
        invoke_error("cant get transcription parameters 2\n", token_cast, NULL);
    parameters->comment_size = ft_strlen(((t_token *)current_token->stuff)->string) - 2;

    //assuming 0 comment size is ok;
    // if (!parameters->comment_size)
    //     invoke_error(GENERIC_ERROR_MESSAGE);

    // distance = ((t_token*)current_token->stuff)->distance;
    // current_token = get_last_element(current_token);
    // parameters->exec_code_size = ((t_token *)current_token->stuff)->distance - distance;

    current_token = get_last_element(tokens);
    token_cast = (t_token *)current_token->stuff;
    parameters->exec_code_size = ((t_token *)current_token->stuff)->distance -
    parameters->name_size - parameters->comment_size;
    if (parameters->exec_code_size < 0)
        invoke_error("parameters are broken\n", token_cast, NULL);
    return (parameters);
}