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

//
//this works the same way for both direct and indirect values as its implemented right now;
//
char *get_number_encoding(t_token *token)
{
    char *number_encoding;
    char *value_substring;
    int number;

    if (token->string[0] == '-')
        value_substring = token->string;
    else if (is_a_member(DIGITS, token->string[0])) //starts with a digit - ergo a number? 
        value_substring = token->string;
    else
        value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1);
    number = ft_atoi(value_substring);
    if (number < 0)
    {
        ; // why am i checking this? 
    }
    number_encoding = decimal_to_hex_mk2(number, token->size);
    return (number_encoding);
}

char *get_label_encoding(t_generic_list *token,
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
//
//
//

char *get_indirect_address_encoding(t_token *token, t_generic_list *tokens)
{
    char *value_encoding;
    int address_value;
    int distance_to_operation;
    int actual_distance;

    distance_to_operation = get_distance_to_the_previous_operation(token, tokens);
    if (distance_to_operation < 0)
        invoke_error("indirect addressing is broken", token, NULL);
    address_value = ft_atoi_base(token->string, 16);
    actual_distance = distance_to_operation + address_value;
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
            // encoding_string = get_direct_label_encoding(token, tokens, labels);
            encoding_string = get_label_encoding(token, tokens, labels);
        else
            // encoding_string = get_direct_number_encoding(current_token);
            encoding_string = get_number_encoding(current_token);
    }
    else if (current_token->argument_type == indirect) //this might be wrong;
    {
        if (current_token->string[1] == LABEL_CHAR)
            encoding_string = get_label_encoding(token, tokens, labels);
        else
            encoding_string = get_number_encoding(current_token);
    }
    encoding = new_generic_list(encoding_string);
    *bytes_encoded = *bytes_encoded + current_token->size;
    return (encoding);
}
