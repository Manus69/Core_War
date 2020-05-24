#include "tokens.h"
#include "function_prototypes.h"
#include "operation_table.h"

char *get_registry_encoding(t_token *token)
{
    char *registry_encoding;
    char *value_substring;
    int registry_value;

    value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1); //leak;
    registry_value = ft_atoi(value_substring);
    if (registry_value < 0 || registry_value > 16)
        invoke_error("registry number out of range\n", token, NULL); //msg
    registry_encoding = decimal_to_hex_mk2(registry_value, token->size);
    return (registry_encoding);
}

char *get_direct_number_encoding(t_token *token)
{
    char *number_encoding;
    char *value_substring;

    value_substring = ft_strsub(token->string, 1, ft_strlen(token->string) - 1);
    number_encoding = decimal_to_hex_mk2(ft_atoi(value_substring), token->size);
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
    label_encoding = decimal_to_hex_mk2(distance, current_token->size);
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
    //
    if (!check_number_string(value_substring))
        invoke_error("argement is bigger than int in absolute value\n", token, NULL);
    //
    number = ft_atoi(value_substring);
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

    int index;
    
    current_token = ((t_token *)token->stuff); 

    index = 0;
    while (!is_a_member(LABEL_CHARS, current_token->string[index]))
        index ++;

    label_name = ft_strsub(current_token->string, index, ft_strlen(current_token->string) - 1);
    distance = get_distance_to_the_label(token, label_name, tokens, labels);
    label_encoding = decimal_to_hex_mk2(distance, current_token->size);
    return (label_encoding);
}
//
//
//

t_generic_list *encode_argument(t_generic_list *token,
t_generic_list *tokens, t_generic_list *labels)
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
            encoding_string = get_label_encoding(token, tokens, labels);
        else
            encoding_string = get_number_encoding(current_token);
    }
    else if (current_token->argument_type == indirect) //this might be wrong;
    {
        if (current_token->string[0] == LABEL_CHAR)
            encoding_string = get_label_encoding(token, tokens, labels);
        else
            encoding_string = get_number_encoding(current_token);
    }
    encoding = new_generic_list(encoding_string);
    return (encoding);
}
