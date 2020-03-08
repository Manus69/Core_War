#include "tokens.h"
#include "function_prototypes.h"
#include "operation_table.h"

char *get_registry_encoding(t_token *token)
{
    char *registry_encoding;
    char *value_substring;

    value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1);
    registry_encoding = decimal_to_hex(ft_atoi(value_substring), token->size);
    return (registry_encoding);
}

char *get_direct_number_encoding(t_token *token)
{
    char *number_encoding;
    char *value_substring;

    value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1);
    number_encoding = decimal_to_hex(ft_atoi(value_substring), token->size);
    return (number_encoding);
}

char *get_direct_label_encoding(t_generic_list *token,
t_generic_list *tokens, t_generic_list *labels)
{
    int distance;
    char *label_name;
    t_token *current_token;
    char *label_encoding;
    
    current_token = ((t_token *)token->stuff);
    label_name = ft_strsub(current_token->string, 2, ft_strlen(current_token->string) - 1);
    distance = get_distance_to_the_label(token, label_name, tokens, labels);
    label_encoding = decimal_to_hex(distance, current_token->size);
    return (label_encoding);
}

t_generic_list *encode_argument(t_generic_list *token,
t_generic_list *tokens, t_generic_list *labels, int *bytes_encoded)
{
    t_generic_list *encoding;
    t_token *current_token;
    char *encoding_string;

    current_token = (t_token *)token->stuff;
    if (current_token->argument_type == registry)
        encoding_string = get_registry_encoding(current_token);
    else if (current_token->argument_type == direct)
    {
        if (current_token->string[1] == LABEL_CHAR)
            encoding_string = get_direct_label_encoding(token, tokens, labels);
        else
            encoding_string = get_direct_number_encoding(current_token);
    }
    else if (current_token->argument_type == indirect)
        encoding_string = ft_strdup("working on it");
    else
        encoding_string = ft_strdup("this is broken");
    encoding = new_generic_list(encoding_string);
    *bytes_encoded = *bytes_encoded + current_token->size;
    return (encoding);
}
