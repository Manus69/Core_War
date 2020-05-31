#include "tokens.h"
#include "function_prototypes.h"

enum e_status_code get_status_code(t_token *token)
{
    if (token->type == command_name)
        return (name_code);
    if (token->type == command_comment)
        return (comment_code);
    return (invoke_error("wrong token\n", token, NULL, NULL)); //should never be executed
}

void set_status(t_container *container, t_token *token)
{
    short shifted_number;
    enum e_status_code status_code;

    status_code = get_status_code(token);
    shifted_number = (1 << status_code);
    if (container->status & shifted_number)
        invoke_error("token duplication\n", token, NULL, container);
    container->status = (container->status | shifted_number);
}