#include "function_prototypes.h"

static void classify_after_null(t_token *current_token, t_token *previous_token)
{
    if (is_command_name(current_token->string))
        current_token->type = command_name;
    else if (is_command_comment(current_token->string))
        current_token->type = command_comment;
    else if (is_new_line(current_token->string))
        current_token->type = new_line;
}

static void classify_after_new_line(t_token *current_token, t_token *previous_token)
{
    if (is_new_line(current_token->string))
        current_token->type = new_line;
    else if (is_label(current_token->string))
        current_token->type = label;
    else if (is_operation(current_token->string))
        current_token->type = operation;
    else if (is_command_name(current_token->string))
        current_token->type = command_name;
    else if (is_command_comment(current_token->string))
        current_token->type = command_comment;
}

static void classify_after_label(t_token *current_token, t_token *previous_token)
{
    if (is_new_line(current_token->string))
        current_token->type = new_line;
    else if (is_operation(current_token->string))
        current_token->type = operation;
}

static void classify_after_argument(t_token *current_token, t_token *previous_token)
{
    if (is_argument_separator(current_token->string))
        current_token->type = comma;
    else if (is_new_line(current_token->string))
        current_token->type = new_line;
}

static void classify_after_operation(t_token *current_token, t_token *previous_token)
{
    if (check_argument_token(current_token))
    ;
    else if (is_new_line(current_token->string))
        current_token->type = new_line;
}

int     check_argument_token(t_token *token)
{
    if (is_registry(token->string))
    {
        token->type = argument;
        token->argument_type = registry;
        return (1);
    }
    else if (is_direct(token->string))
    {
        token->type = argument;
        token->argument_type = direct;
        return (1);
    }
    else if (is_indirect(token->string))
    {
        token->type = argument;
        token->argument_type = indirect;
        return (1);
    }
    return (0);
}

void classify_token(t_token *current_token, t_token *previous_token)
{
    if (!current_token)
        return ;
    if (ft_strcmp(current_token->string, "NULL TOKEN") == 0)
        current_token->type = null;
    else if (previous_token == NULL)
        classify_after_null(current_token, previous_token);
    else if (previous_token->type == new_line)
        classify_after_new_line(current_token, previous_token);
    else if (previous_token->type == command_name && is_string(current_token->string))
        current_token->type = champ_name;
    else if (previous_token->type == command_comment && is_string(current_token->string))
        current_token->type = champ_comment;
    else if (previous_token->type == label)
        classify_after_label(current_token, previous_token);
    else if (previous_token->type == operation)
        classify_after_operation(current_token, previous_token);
    else if (previous_token->type == argument)
        classify_after_argument(current_token, previous_token);
    else if (previous_token->type == comma && check_argument_token(current_token))
        return ;
    else if (previous_token->type == champ_name && is_new_line(current_token->string))
        current_token->type = new_line;
    else if (previous_token->type == champ_comment && is_new_line(current_token->string))
        current_token->type = new_line;
}