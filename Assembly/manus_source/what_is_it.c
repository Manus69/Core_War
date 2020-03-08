#include "function_prototypes.h"
#include "tokens.h"
#include "operation_table.h"

int     generic_token_string_check(char *string, char character, int start)
{
    int length;

    length = ft_strlen(string);
    if (length < 2)
        return (0);
    if (start && (string[0] != character))
        return (0);
    if (!start && (string[length - 1] != character))
        return (0);
    return (1);
}

int     check_substring_characters(char *string, int start_index, int end_index, char *set)
{
    int n;

    if (end_index < start_index)
        return (0);
    n = start_index;
    while (n <= end_index)
    {
        if (!is_a_member(set, string[n]))
            return (0);
        n = n + 1;
    }
    return (1);
}

int     is_label(char *string)
{
    int n;

    if (!generic_token_string_check(string, LABEL_CHAR, 0))
        return (0);
    n = 0;
    while (string[n] != LABEL_CHAR)
    {
        if (!is_a_member(LABEL_CHARS, string[n]))
            return (0);
        n = n + 1;
    }
    return (1);
}

int     check_symbol(char *string, char symbol)
{
    if (ft_strlen(string) == 1 && string[0] == symbol)
        return (1);
    return (0);
}

int     is_quotation_mark(char *string)
{
    return (check_symbol(string, '"'));
}

int     is_comment_character(char *string)
{
    return (check_symbol(string, COMMENT_CHAR));
}

int     is_new_line(char *string)
{
    return (check_symbol(string, '\n'));
}

int     is_argument_separator(char *string)
{
    return (check_symbol(string, SEPARATOR_CHAR));
}

int     is_string_in_array(char *string, char **string_array)
{
    int n;
    char *current_string;

    n = 0;
    current_string = string_array[0];
    while (current_string)
    {
        if (ft_strcmp(current_string, string) == 0)
            return (1);
        n = n + 1;
        current_string = string_array[n];
    }
    return (0);
}

int     is_operation(char *string)
{
   return (is_string_in_array(string, g_operation_names));
}

int     is_command(char *string)
{
    return (is_string_in_array(string, g_command_names));
}

//argument classification

int     is_registry(char *string)
{
    int n;
    
    if (!generic_token_string_check(string, 'r', 1))
        return (0);
    n = 1;
    while (string[n] != '\0')
    {
        if (!is_a_member(DIGITS, string[n]))
            return (0);
        n = n + 1;
    }
    return (1);
}

int     is_direct(char *string)
{
    int n;
    int length;
    
    if (!generic_token_string_check(string, DIRECT_CHAR, 1))
        return (0);
    n = 1;
    length = ft_strlen(string);
    if (string[n] == LABEL_CHAR && (length > 2))
    {
        if (check_substring_characters(string, 2, length - 1, LABEL_CHARS))
            return (1);
    }
    else if (is_a_member(DIGITS, string[n]))
    {
        if (check_substring_characters(string, 1, length - 1, DIGITS))
            return (1);
    }
    return (0);
}

int     is_indirect(char *string)
{
    int n;
    int length;

    n = 0;
    length = ft_strlen(string);
    if (string[n] == LABEL_CHAR && (length > 1))
    {
        if (check_substring_characters(string, 1, length - 1, LABEL_CHARS))
            return (1);
    }
    else if (is_a_member(DIGITS, string[n]))
    {
        if (check_substring_characters(string, 0, length - 1, DIGITS))
            return (1);
    }
    return (0);
}

//

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

void set_token_size(t_token *token)
{
    enum e_token_type operation_type;

    if (token->type == string)
        token->size = ft_strlen(token->string);
    else if (token->type == operation)
    {
        operation_type = get_operation_name(token);
        if (op_tab[operation_type].arg_code_flag == 1)
            token->size = 2;
        else
            token->size = 1;
    }
    else if (token->type == argument)
    {
        if (token->argument_type == registry)
            token->size = REG_SIZE;
        else if (token->argument_type == direct)
            token->size = DIR_SIZE;
        else if (token->argument_type == indirect)
            token->size = IND_SIZE;
    }
}