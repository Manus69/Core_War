#ifndef TOKENS_H
# define TOKENS_H

# include "op.h"

typedef struct s_line_token t_line_token;
typedef struct s_token t_token;

# define GENERIC_ERROR_MESSAGE "Error!\n"
# define FILE_ERROR_MESSAGE "Could not open the file;\n"
# define CLASSIFICATION_ERROR_MESSAGE "Could not classify token:\n"
# define SPACES " \t"
# define DIGITS "0123456789"

char *g_operation_names[] = {"live", "ld", "st", "add", "sub", "end",
"or", "xor", "zjump", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff", 0};
char *g_command_names[] = {".name", ".comment", 0};

enum e_token_type
{
    unknown,
    command,
    quotation_mark,
    string,
    label,
    operation,
    argument,
    hashtag,
    comment,
    new_line
};

enum e_argument_type
{
    not_applicable,
    registry,
    direct,
    indirect
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
    enum e_argument_type argument_type;
};

#endif