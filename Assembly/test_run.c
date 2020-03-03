#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "function_prototypes.h"
#include <fcntl.h>

char g_separators[] = {' ', '\t', SEPARATOR_CHAR, 0}; //null byte to terminate the array;

t_token *new_token(char *string, enum e_token_type type)
{
    t_token *token;

    token = mallokill(sizeof(t_token));
    token->string = string;
    if (type == 0)
        token->type = unknown;
    else
        token->type = type;
    return (token);
}

t_token *get_next_token(int *n, char *line)
{
    int m;
    t_token *token;
    char *substring;
    char test;

    token = NULL;
    while (is_a_member(g_separators, line[*n])) //what about the degenerate cases?
    {
        *n = *n + 1;
    }
    m = *n;
    while (line[m] != '\0' && (!is_a_member(g_separators, line[m])))
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
        while (is_a_member(SPACES, line[n]))
            n = n + 1;
        token = get_next_token(&n, line);
        //
        display_token(token);
        //
        token_list = add_to_list(token_list, token);
        //n = n + 1;
    }
    return (token_list);
}

int main()
{
    char *current_line;
    int file;
    t_generic_list *tokens;
    t_generic_list *line_tokens;
    t_generic_list *last_element;

    file = open("/home/anus/projects/core_war/Assembly/test_champ.s", O_RDONLY);
    if (file < 0)
    {
        ft_printf("%s", FILE_ERROR_MESSAGE);
        exit(1);
    }
    tokens = NULL;
    last_element = NULL;
    while (get_next_line(file, &current_line) > 0)
    {
        // ft_printf("%s\n", current_line);
        line_tokens = line_to_tokens(current_line);
        tokens = concatenate_lists(tokens, line_tokens, last_element);
        last_element = get_last_element(line_tokens);
        free(current_line);
        // destroy_generic_list(&line_tokens);
    }
    return (0);
}