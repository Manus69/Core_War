#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"

void classify_token(t_token *current_token, t_token *previous_token)
{
    if (!current_token)
        return ;
    if (ft_strcmp(current_token->string, "NULL TOKEN") == 0)
        current_token->type = null;
    else if (previous_token == NULL)
    {
        if (is_command_name(current_token->string))
            current_token->type = command_name;
        else if (is_command_comment(current_token->string))
            current_token->type = command_comment;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_comment_character(current_token->string))
            current_token->type = comment_char;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == new_line)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_label(current_token->string))
            current_token->type = label;
        else if (is_comment_character(current_token->string))
            current_token->type = comment_char;
        else if (is_operation(current_token->string))
            current_token->type = operation;
        else if (is_command_name(current_token->string))
            current_token->type = command_name;
        else if (is_command_comment(current_token->string))
            current_token->type = command_comment;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == command_name)
    {
        if (is_string(current_token->string))
            current_token->type = champ_name;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == command_comment)
    {
        if (is_string(current_token->string))
            current_token->type = champ_comment;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == label)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_operation(current_token->string))
            current_token->type = operation;
        else if (is_comment_character(current_token->string))
            current_token->type = comment_char;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == operation)
    {
        if (is_comment_character(current_token->string))
            current_token->type = comment_char;
        else if (check_argument_token(current_token))
            ;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == argument)
    {
        if (is_comment_character(current_token->string))
            current_token->type = comment_char;
        else if (is_argument_separator(current_token->string))
            current_token->type = comma;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == comma)
    {
        if (is_comment_character(current_token->string))
            current_token->type = comment_char;
        else if (check_argument_token(current_token))
            ;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == comment_char)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            current_token->type = comment;
    }
    else if (previous_token->type == comment)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            current_token->type = comment;
    }
    else if (previous_token->type == string) //this has to go
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_comment_character(current_token->string))
            current_token->type = comment_char;
        else
            current_token->type = string;
    }
    else if (previous_token->type == champ_name)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
    }
    else if (previous_token->type == champ_comment)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
    }
}

static void classification_check(t_container *container, t_token *current_token)
{
    if (current_token->type != new_line)
        invoke_error("no new line at the end of file\n", NULL, NULL);
    if (!(container->status >> 1) & 1)
        invoke_error("name command is missing\n", NULL, NULL);
    if (!(container->status & 1))
        invoke_error("comment command is missing\n", NULL, NULL);
}

void classify_all_tokens(t_container *container)
{
    t_token *current_token;
    t_token *previous_token;
    t_generic_list *current_item;

    previous_token = NULL;
    current_item = container->tokens;

    while (current_item)
    {
        if (!current_item->stuff)
            invoke_error("current token is bricked!\n previous token:", previous_token, NULL);
        current_token = current_item->stuff;
        classify_token(current_token, previous_token);
        
        if (current_token->type == label)
            container->labels = add_to_list(container->labels, current_token);
        else if (current_token->type == command_name)
            set_status(container, current_token);
        else if (current_token->type == command_comment)
            set_status(container, current_token);

        current_item = current_item->next;
        previous_token = current_token;
    }
    classification_check(container, current_token);        
}
