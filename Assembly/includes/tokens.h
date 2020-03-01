#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_line_token t_line_token;

struct s_line_token
{
    int index;
    char *label;
    char *operation;
    char *arguments;
};

#endif