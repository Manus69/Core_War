#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"

void classify_token(t_token *current_token, t_token *previous_token, int verbose) //is verbose even necessary? 
{
    if (!current_token)
        return ;
    if (ft_strcmp(current_token->string, "NULL TOKEN") == 0)
        current_token->type = null;
    else if (previous_token == NULL)
    {
        if (is_command_name(current_token->string))
            current_token->type = command_name;
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
        if (is_quotation_mark(current_token->string))
            current_token->type = opening_quotation_mark;
        else if (is_string(current_token->string))
            current_token->type = string;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
    }
    else if (previous_token->type == command_comment)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = opening_quotation_mark;
        else if (is_string(current_token->string))
            current_token->type = string;
        else if (is_multistring_start(current_token->string))
            current_token->type = multiline_string;
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
    else if (previous_token->type == opening_quotation_mark)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = closing_quotation_mark;
        else if (is_string(current_token->string))
            current_token->type = string;
        else
            invoke_error("something is wrong", current_token, NULL);
    }
    else if (previous_token->type == closing_quotation_mark)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = opening_quotation_mark;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            invoke_error(CLASSIFICATION_ERROR_MESSAGE, current_token, NULL);
        
    }
    else if (previous_token->type == string)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = closing_quotation_mark;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            current_token->type = string;
    }
    else if (previous_token->type == multiline_string)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = closing_quotation_mark;
        else if (is_multistring_end(current_token->string))
            current_token->type = multiline_string;
        else if (is_multistring(current_token->string))
            current_token->type = multiline_string;
    }
    // set_token_size(current_token);
}

void classify_all_tokens(t_generic_list *tokens, t_generic_list **labels, int verbose)
{
    t_token *current_token;
    t_token *previous_token;
    t_generic_list *current_item;

    previous_token = NULL;
    current_item = tokens;

    while (current_item)
    {
        if (!current_item->stuff)
            invoke_error("current token is bricked!\n previous token:", previous_token, NULL);
        current_token = current_item->stuff;
        classify_token(current_token, previous_token, verbose);
        if (current_token->type == label)
            *labels = add_to_list(*labels, current_token);
        current_item = current_item->next;
        previous_token = current_token;
    }
}