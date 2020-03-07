#include "tokens.h"
#include "function_prototypes.h"
#include "operation_table.h"

char *get_registry_encoding(t_token *token)
{
    char *registry_encoding;
    char *value_substring;

    value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1);
    registry_encoding = decimal_to_hex(ft_atoi(value_substring), T_REG);
    return (registry_encoding);
}

char *get_direct_number_encoding(t_token *token)
{
    char *registry_encoding;
    char *value_substring;

    value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1);
    registry_encoding = decimal_to_hex(ft_atoi(value_substring), T_DIR);
    return (registry_encoding);
}