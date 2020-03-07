#ifndef TOKENS_H
# define TOKENS_H

# include "op.h"

# define GENERIC_ERROR_MESSAGE "Error!\n"
# define FILE_ERROR_MESSAGE "Could not open the file;\n"
# define CLASSIFICATION_ERROR_MESSAGE "Could not classify token:\n"
# define SPACES " \t"
# define DIGITS "0123456789"
# define NUMBER_SYSTEM_BASE 16
# define ARG_ENCODING_SIZE 1 //is there a constant in the header already? 

static char *g_operation_names[] = {"live", "ld", "st", "add", "sub", "end",
"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff", 0};
static char *g_command_names[] = {".name", ".comment", 0};
static char g_separators[] = {'"', COMMENT_CHAR, SEPARATOR_CHAR, 0}; //null byte to terminate the array;
static char g_spaces[] = {' ', '\t', 0};

typedef struct s_line_token t_line_token;
typedef struct s_token t_token;

enum e_token_type
{
    unknown,
    command,
    opening_quotation_mark,
    closing_quotation_mark,
    string,
    label,
    operation,
    argument,
    comma,
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