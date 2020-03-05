#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "function_prototypes.h"
#include <fcntl.h>

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
    return (token);
}

t_token *get_next_token(int *n, char *line)
{
    int m;
    t_token *token;
    char *substring;
    char test;

    token = NULL;
    //
    test = line[*n];
    //
    if (is_a_member(g_separators, line[*n]))
    {
        substring = ft_strsub(line, *n, 1);
        token = new_token(substring, 0);
        *n = *n + 1;
        return (token);
    }
    m = *n;
    while (line[m] != '\0' && !is_a_member(g_separators, line[m]) && !is_a_member(g_spaces, line[m]))
    {
        test = line[m];
        m = m + 1;
    }
    if (m - *n > 0)
    {
        substring = ft_strsub(line, *n, m - *n);
        token = new_token(substring, 0);
    }
    *n = m;
    return (token);
}

t_generic_list *line_to_tokens(char *line)
{
    int n;
    t_token *token;
    t_generic_list *token_list;

    n = 0;
    token = NULL;
    token_list = NULL;
    while (line[n] != '\0')
    {
        while (is_a_member(g_spaces, line[n]))
            n = n + 1;
        token = get_next_token(&n, line);
        //
        // display_token(token);
        //
        token_list = add_to_list(token_list, token);
    }
    return (token_list);
}

void classify_token(t_token *current_token, t_token *previous_token, int verbose)
{
    if (!current_token)
        return ;
    if (previous_token == NULL)
    {
        if (is_command(current_token->string))
            current_token->type = command;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == new_line)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_label(current_token->string))
            current_token->type = label;
        else if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (is_operation(current_token->string))
            current_token->type = operation;
        else if (is_command(current_token->string))
            current_token->type = command;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == command)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = quotation_mark;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == label)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_operation(current_token->string))
            current_token->type = operation;
        else if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == operation)
    {
        if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (check_argument_token(current_token))
            ;
        else if (is_new_line(current_token->string)) //is this legal?
            current_token->type = new_line;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == argument)
    {
        if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (is_argument_separator(current_token->string))
            current_token->type = comma;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == comma)
    {
        if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (check_argument_token(current_token))
            ;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == hashtag)
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
    else if (previous_token->type == quotation_mark)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = quotation_mark;
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            current_token->type = string;
    }
    else if (previous_token->type == string)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = quotation_mark;
        else
            current_token->type = string;
    }
}

void classify_all_tokens(t_generic_list *tokens, int verbose)
{
    t_token *current_token;
    t_token *previous_token;
    t_generic_list *current_item;

    previous_token = NULL;
    current_item = tokens;
    while (current_item)
    {
        current_token = current_item->stuff;
        classify_token(current_token, previous_token, verbose);
        current_item = current_item->next;
        previous_token = current_token;
    }
}

int main()
{
    char *current_line;
    int file;
    t_generic_list *tokens;
    t_generic_list *line_tokens;
    t_generic_list *last_element;

    file = open("/home/anus/projects/core_war/Assembly/test_file.s", O_RDONLY);
    if (file < 0)
    {
        ft_printf("%s", FILE_ERROR_MESSAGE);
        exit(1);
    }
    tokens = NULL;
    last_element = NULL;
    while (get_next_line(file, &current_line) > 0) //careful about the trailing \n; the thing is fucked up;
    {
        line_tokens = line_to_tokens(current_line);
        if (line_tokens)
        {
            tokens = concatenate_lists(tokens, line_tokens, last_element);
            last_element = get_last_element(line_tokens);
            last_element = add_to_list(last_element, new_token("\n", new_line));
            last_element = last_element->next;
        }
        else if (!line_tokens && !tokens)
        {
            tokens = new_generic_list(new_token("\n", new_line));
            last_element = tokens;
        }
        else if (!line_tokens)
        {
            tokens = concatenate_lists(tokens, new_generic_list(new_token("\n", new_line)), last_element);
            last_element = last_element->next;
        }
        free(current_line);
    }
    classify_all_tokens(tokens, 1);
    display_all_tokens(tokens);
    return (0);
}