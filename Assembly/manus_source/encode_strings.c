#include "tokens.h"
#include "function_prototypes.h"

int check_ascii_string(const char *string)
{
    unsigned int n;

    n = 0;
    while (string[n] != '\0')
    {
        if (!ft_isascii(string[n]))
            return (0);
        n = n + 1;
    }
    return (1);
}

t_generic_list *get_null_padding(int number_of_bytes)
{
    int n;
    t_generic_list *encoding;

    n = 0;
    encoding = NULL;
    while (n < number_of_bytes)
    {
        encoding = add_to_list(encoding, ft_strdup("00"));
        n = n + 1;
    }
    return (encoding);
}

t_generic_list *encode_string(t_token *token)
{
    int n;
    t_generic_list *encoding;
    char *current_byte;
    void *pointer;

    n = 0;
    encoding = NULL;
    if (!check_ascii_string(token->string))
        invoke_error("nonascii characters in string\n", NULL, token->string); //message
    while (token->string[n] != '\0')
    {       
        if (token->string[n] != '"')
        {
            current_byte = ft_itoa_base_local(token->string[n], NUMBER_SYSTEM_BASE);
            if (ft_strlen(current_byte) < 2)
            {
                pointer = current_byte;
                current_byte = concat("0", current_byte);
                free(pointer);
            }
            encoding = add_to_list(encoding, current_byte);
        }
        n = n + 1;
    }
    return (encoding);
}

t_generic_list *encode_string_tokens(t_generic_list *tokens)
{
    t_generic_list *current_token;
    t_generic_list *encoding;
    t_generic_list *string_encoding;
    t_generic_list *last_element;

    current_token = tokens;
    encoding = NULL;
    last_element = NULL;
    while (((t_token *)current_token->stuff)->type == string)
    {
        string_encoding = encode_string((t_token *)current_token->stuff);
        encoding = concatenate_lists(encoding, string_encoding, last_element);
        last_element = get_last_element(string_encoding);
        current_token = current_token->next;
        if (((t_token *)current_token->stuff)->type == string)
        {
            last_element = add_to_list(last_element, ft_itoa_base(' ', NUMBER_SYSTEM_BASE));
            last_element = last_element->next;
        }
    }
    return (encoding);
}