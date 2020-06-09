#ifndef CONSTANTS_H
# define CONSTANTS_H

# include "op.h"

# define GENERIC_ERROR_MESSAGE "Error!\n"
# define FILE_ERROR_MESSAGE "Could not open the file;\n"
# define CLASSIFICATION_ERROR_MESSAGE "Could not classify token:\n"
# define ARGUMENT_ERROR_MESSAGE "Argument error;\n"
# define UNEXPECTED_ERROR "Something is wrong;\n"
# define SPACES " \t"
# define DIGITS "0123456789"
# define NUMBER_SYSTEM_BASE 16
# define PADDING_SIZE 4
# define BUFFER_SIZE 1024

//depreciated; 
// # define ARG_ENCODING_SIZE 1 //is there a constant in the header already?
// # define REG_ARG_SIZE 1
// # define DIR_ARG_SIZE 2
// # define IND_ARG_SIZE 2 //how much is it really?
//

# define REGISTRY_NAME_SIZE T_REG
# define REGISTRY_SIZE REG_SIZE
# define DIRECT_VALUE_SIZE REGISTRY_SIZE
# define DIRECT_ADDRESS_SIZE IND_SIZE
# define INDIRECT_VALUE_SIZE IND_SIZE


static const char		*g_operation_names[] = {"live", "ld", "st", "add", "sub", "and",
"or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi", "lfork", "aff", 0};
static const char		*g_command_names[] = {".name", ".comment", 0};
static const char		g_separators[] = {'"', '\n', COMMENT_CHAR, COMMENT_CHAR_ALT, SEPARATOR_CHAR, 0}; //null byte to terminate the array;
static const char		g_spaces[] = {' ', '\t', 0};
static const char		g_comment_chars[] = {COMMENT_CHAR, COMMENT_CHAR_ALT, 0};

#endif
