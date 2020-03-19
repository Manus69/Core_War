#include "tokens.h"
#include "function_prototypes.h"

t_generic_list *get_next_typed_token(t_generic_list *tokens, enum e_token_type type)
{
    t_generic_list *current_token;
    t_token *token_cast;

    current_token = tokens;
    while (current_token)
    {
        token_cast = (t_token *)current_token->stuff;
        if (token_cast->type == type)
            return (current_token);
        current_token = current_token->next;
    }
    invoke_error(GENERIC_ERROR_MESSAGE); //change the message later;
    return (NULL); //never executed;
}

t_transcription_parameters *get_transcription_parameters(t_generic_list *tokens)
{
    t_transcription_parameters *parameters;
    t_generic_list *current_token;
    t_token *token_cast;
    int distance;

    parameters = mallokill(sizeof(t_transcription_parameters));
    current_token = get_next_typed_token(tokens, opening_quotation_mark);
    distance = ((t_token *)current_token->stuff)->distance;
    current_token = get_next_typed_token(current_token, closing_quotation_mark);
    parameters->name_size = ((t_token *)current_token->stuff)->distance - distance;
    if (!parameters->name_size)
        invoke_error(GENERIC_ERROR_MESSAGE); //get the right message;
    current_token = get_next_typed_token(current_token, opening_quotation_mark);
    distance = ((t_token *)current_token->stuff)->distance;
    current_token = get_next_typed_token(current_token, closing_quotation_mark);
    parameters->comment_size = ((t_token *)current_token->stuff)->distance - distance;
    if (!parameters->name_size)
        invoke_error(GENERIC_ERROR_MESSAGE);
    distance = ((t_token*)current_token->stuff)->distance;
    current_token = get_last_element(current_token);
    parameters->exec_code_size = ((t_token *)current_token->stuff)->distance - distance;
    return (parameters);
}