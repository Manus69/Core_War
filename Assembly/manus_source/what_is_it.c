#include "function_prototypes.h"
#include "tokens.h"

int     is_label(t_token *current_token, t_token *previous_token)
{
    int n;
    int length;

    if (previous_token && (previous_token->type != new_line)) //make all the functions uniform;
        return (0);
    length = ft_strlen(current_token->string);
    if (length < 2)
        return (0);
    if (current_token->string[length - 1] != LABEL_CHAR)
        return (0);
    n = 0;
    while (n < length - 1)
    {
        if (!is_a_member(LABEL_CHARS, current_token->string[n]))
            return (0);
        n = n + 1;
    }
    return (1);
}

int     is_quotation_mark(t_token *current_token, t_token *previous_token)
{
    if (ft_strlen(current_token->string) == 1 && current_token->string[0] == '"')
        return (1);
    return (0);
}

int     is_hashtag(t_token *current_token, t_token *previous_token)
{
    if (ft_strlen(current_token->string) == 1 && current_token->string[0] == '#')
        return (1);
    return (0);
}

int     is_new_line(t_token *current_token, t_token *previous_token)
{
    if (ft_strlen(current_token->string) == 1 && current_token->string[0] == '\n')
        return (1);
    return (0);
}

int     is_operation(t_token *current_token, t_token *previous_token)
{
    int n;
    char *current_string;

    n = 0;
    current_string = g_operation_names[n];
    while (current_string)
    {
        if (ft_strcmp(current_string, current_token->string) == 0)
            return (1);
        n = n + 1;
        current_string = g_operation_names[n];
    }
    return (0);
}

int     is_command(t_token *current_token, t_token *previous_token)
{
    int n;
    char *current_string;

    n = 0;
    current_string = g_command_names[n];
    while (current_string)
    {
        if (ft_strcmp(current_string, current_token->string) == 0)
            return (1);
        n = n + 1;
        current_string = g_command_names[n];
    }
    return (0);
}