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
    return (token);
}

void skip_spaces(int *n, char *line)
{
    while (ft_strstr(SPACES, &line[*n]) != NULL)
        *n = *n + 1;
}

t_generic_list *line_to_tokens(char *line)
{
    int n;
    t_token *token;
    t_generic_list *token_list;

    n = 0;
    token = NULL;
    token_list = NULL;
    // skip_spaces(&n, line);
    while (line[n] != '\0')
    {
        if (ft_strstr(SPACES, &line[n]) != NULL)
            skip_spaces(&n, line);
        
        n = n + 1;
    }
    return (token_list);
}

int main()
{
    char *current_line;
    int file;
    t_generic_list *tokens;

    file = open("Makefile", O_RDONLY);
    if (file < 0)
    {
        // ft_printf("%s", FILE_ERROR_MESSAGE);
        write(1, FILE_ERROR_MESSAGE, ft_strlen(FILE_ERROR_MESSAGE));
        exit(1);
    }
    while (get_next_line(file, &current_line) > 0)
    {
        ft_printf("%s\n", current_line);
        // line_to_tokens(current_line);
        ;
    }
    
    return (0);
}