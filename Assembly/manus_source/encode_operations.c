#include "tokens.h"
#include "function_prototypes.h"
#include "operation_table.h"
#include "generic_list.h"
#include <stdarg.h>

char *get_string_of_chars(unsigned int size, char c)
{
    char *string;
    unsigned int n;

    string = ft_strnew(size);
    n = 0;
    while (n < size)
    {
        string[n] = c;
        n ++;
    }
    return (string);
}

char *join_and_free(char *lhs, char *rhs)
{
    char *result;

    result = ft_strjoin(lhs, rhs);
    free(lhs);
    free(rhs);

    return (result);
}

char *pad_with_chars(char *string, unsigned int pad_size, char c, int side)
{
    char *result;
    char *pad_string;

    pad_string = get_string_of_chars(pad_size, c);
    if (side == -1)
        result = concat(pad_string, string);
    else if (side == 1)
        result = concat(string, pad_string);
    else
        invoke_error("shit!\n", NULL, NULL); //msg?
    free(pad_string);

    return (result);
}

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
    // char *saved_pointer;
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

        // saved_pointer = byte_string;
        // byte_string = ft_strjoin(byte_string, byte);
        // free(saved_pointer);
        // free(byte);
        byte_string = join_and_free(byte_string, byte);
        n = n + 1;
    }
    byte_string = pad_with_chars(byte_string, (MAX_ARGS_NUMBER - n) * 2, '0', 1);
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

static char *get_type_byte_code(t_generic_list *argument_list, int arg_count)
{
    // t_token *token_cast;
    void *pointer;
    char *byte_code;
    char *byte;
    t_generic_list *current_token;
    
    byte_code = ft_strdup("");
    current_token = argument_list;
    while (arg_count)
    {
        // token_cast = ((t_token *)argument_list->stuff);
        if (((t_token *)current_token->stuff)->argument_type == registry)
            byte = ft_strdup("01");
        else if (((t_token *)current_token->stuff)->argument_type == direct)
            byte = ft_strdup("10");
        else if (((t_token *)current_token->stuff)->argument_type == indirect)
            byte = ft_strdup("11");
        else
            byte = NULL;
        if (byte)
        {
            pointer = byte_code;
            byte_code = ft_strjoin(byte_code, byte);
            arg_count --;
            free(pointer);
            free(byte);
        }
        current_token = current_token->next;
    }
    return (byte_code);
}

t_generic_list *encode_type(t_generic_list *token)
{
    enum e_operation_name operation;
    t_generic_list *encoding_list_item;
    char *result;
    char *hex_encoding;
    void *pointer;
    unsigned int pad_size;


    operation = get_operation_name((t_token *)token->stuff);
    token = token->next;
    result = get_type_byte_code(token, op_tab[operation].arg_count);
    pointer = result;
    pad_size = (MAX_ARGS_NUMBER - op_tab[operation].arg_count) * 2;
    result = pad_with_chars(result, pad_size, '0', 1);
    hex_encoding = decimal_to_hex_mk2(binary_to_decimal(result), 1);
    encoding_list_item = new_generic_list(hex_encoding);

    free(pointer);
    free(result);
    
    return (encoding_list_item);
}

t_generic_list *encode_operation(t_token *token)
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
    return (encoding);
}

