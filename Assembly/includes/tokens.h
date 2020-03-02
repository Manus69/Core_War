#ifndef TOKENS_H
# define TOKENS_H

typedef struct s_line_token t_line_token;
typedef struct s_token t_token;

# define FILE_ERROR_MESSAGE "Could not open the file;\n"
# define SPACES " \t"

enum e_token_type
{
    unknown,
    command,
    string,
    label,
    operation,
    argument,
    comment,
    new_line
};

struct s_line_token
{
    int index;
    char *label;
    char *operation;
    char *arguments;
};

struct s_token
{
    char *string;
    enum e_token_type type;
};

#endif