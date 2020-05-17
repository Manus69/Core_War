#include "tokens.h"
#include "function_prototypes.h"
#include "operation_table.h"
#include "generic_list.h"
#include <stdarg.h>

char *get_zero_bit_string(int number_of_bytes)
{
    int n;
    int number_of_bits;
    char *bit_string;

    number_of_bits = number_of_bytes * 8;
    n = 0;
    bit_string = ft_strnew(number_of_bits);
    while (n < number_of_bits)
    {
        bit_string[n] = '0';
        n = n + 1;
    }
    return (bit_string);
}

char *get_type_encoding(int number_of_arguments, ...)
{
    va_list arg_list;
    t_token *current_token;
    char *byte_string;
    char *byte;
    char *saved_pointer;
    int n;

    if (number_of_arguments > MAX_ARGS_NUMBER)
        invoke_error("can't get the type encoding\n", NULL, NULL); //msg
    n = 0;
    byte_string = ft_strdup("");
    va_start(arg_list, number_of_arguments);
    while (n < number_of_arguments)
    {
        current_token = va_arg(arg_list, t_token *);
        if (current_token->argument_type == registry)
            byte = ft_strdup("01");
        else if (current_token->argument_type == direct)
            byte = ft_strdup("10");
        else if (current_token->argument_type == indirect)
            byte = ft_strdup("11");
        else
            byte = ft_strdup("xx");
        saved_pointer = byte_string;
        byte_string = ft_strjoin(byte_string, byte);
        free(saved_pointer);
        free(byte);
        n = n + 1;
    }
    while (n < MAX_ARGS_NUMBER)
    {
        byte = ft_strdup("00");
        saved_pointer = byte_string;
        byte_string = ft_strjoin(byte_string, byte);
        free(saved_pointer);
        free(byte);
        n = n + 1;
    }
    n = binary_to_decimal(byte_string);
    va_end(arg_list);
    return (decimal_to_hex_mk2(n, 1));
}

enum e_operation_name get_operation_name(t_token *token)
{
    enum e_operation_name operation;

    operation = dummy_operation + 1;
    while (operation < NUMBER_OF_OPERATIONS)
    {
        if (ft_strcmp(token->string, op_tab[operation].op_name) == 0)
            return (operation);
        operation = operation + 1; 
    }
    return (dummy_operation); //should never be executed;
}

t_generic_list *encode_type(t_generic_list *token, int *bytes_encoded)
{
    int argument_count;
    enum e_operation_name operation;
    char *byte;
    char *byte_string;
    char *saved_pointer;
    int n;

    t_token *debug_item;

    n = 0;
    operation = get_operation_name((t_token *)token->stuff);
    argument_count = op_tab[operation].arg_count;
    token = token->next;
    byte_string = ft_strdup("");
    while (n < argument_count)
    {
        if (!token)
            invoke_error("encode type is broken", NULL, NULL);

        debug_item = ((t_token *)token->stuff);

        if (((t_token *)token->stuff)->argument_type == registry)
            byte = ft_strdup("01");
        else if (((t_token *)token->stuff)->argument_type == direct)
            byte = ft_strdup("10");
        else if (((t_token *)token->stuff)->argument_type == indirect)
            byte = ft_strdup("11");
        else
        {
            token = token->next;
            continue ;
        }
        saved_pointer = byte_string;
        byte_string = ft_strjoin(byte_string, byte);
        free(saved_pointer);
        free(byte);
        token = token->next;
        n = n + 1;
    }
    while (n < MAX_ARGS_NUMBER)
    {
        byte = ft_strdup("00");
        saved_pointer = byte_string;
        byte_string = ft_strjoin(byte_string, byte);
        free(saved_pointer);
        free(byte);
        n = n + 1;
    }
    n = binary_to_decimal(byte_string);
    *bytes_encoded = *bytes_encoded + 1;
    // return (new_generic_list(decimal_to_hex(n, 1)));
    return (new_generic_list(decimal_to_hex_mk2(n, 1)));
}

t_generic_list *encode_operation(t_token *token, int *bytes_encoded)
{
    t_generic_list *encoding;
    enum e_operation_name operation;
    char *operation_code;

    operation = dummy_operation + 1;
    while (operation < NUMBER_OF_OPERATIONS)
    {
        if (strcmp(token->string, op_tab[operation].op_name) == 0)
            operation_code = decimal_to_hex_mk2(op_tab[operation].op_code, 1);
        operation = operation + 1;
    }
    encoding = new_generic_list(operation_code);
    *bytes_encoded = *bytes_encoded + 1;
    return (encoding);
}

