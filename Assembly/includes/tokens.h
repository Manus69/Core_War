#ifndef TOKENS_H
# define TOKENS_H

# include "op.h"

# define GENERIC_ERROR_MESSAGE "Error!\n"
# define FILE_ERROR_MESSAGE "Could not open the file;\n"
# define CLASSIFICATION_ERROR_MESSAGE "Could not classify token:\n"
# define ARGUMENT_ERROR_MESSAGE "Argument error;\n"
# define SPACES " \t"
# define DIGITS "0123456789"
# define NUMBER_SYSTEM_BASE 16
# define PADDING_SIZE 4
# define HEADER_BUFFER_SIZE 1e6

//depreciated; 
# define ARG_ENCODING_SIZE 1 //is there a constant in the header already?
# define REG_ARG_SIZE 1
# define DIR_ARG_SIZE 2
# define IND_ARG_SIZE 2 //how much is it really?
//

# define REGISTRY_NAME_SIZE T_REG
# define REGISTRY_SIZE REG_SIZE
# define DIRECT_VALUE_SIZE REGISTRY_SIZE
# define DIRECT_ADDRESS_SIZE IND_SIZE
# define INDIRECT_VALUE_SIZE IND_SIZE


static char *g_operation_names[] = {"live", "ld", "st", "add", "sub", "and",
"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff", 0};
static char *g_command_names[] = {".name", ".comment", 0};
static char g_separators[] = {'"', COMMENT_CHAR, COMMENT_CHAR_ALT, SEPARATOR_CHAR, 0}; //null byte to terminate the array;
static char g_spaces[] = {' ', '\t', 0};

typedef struct s_line_token t_line_token;
typedef struct s_token t_token;
typedef struct s_transcription_parameters t_transcription_parameters;

enum e_token_type
{
    null,
    unknown,
    command_name,
    command_comment,
    opening_quotation_mark,
    closing_quotation_mark,
    string,
    multiline_string,
    // champ_name,
    // champ_comment,
    label,
    operation,
    argument,
    comma,
    comment_char,
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
    int size;
    int distance;
};

struct s_transcription_parameters
{
    int name_size;
    int comment_size;
    int exec_code_size;
};

#endif