#include "tokens.h"
#include "function_prototypes.h"
#include "operation_table.h"
#include "generic_list.h"

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
