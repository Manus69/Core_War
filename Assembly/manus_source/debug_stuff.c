#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"
#include <fcntl.h>

int main()
{
    const char *number_string = "4278415366";
    // const char *number_string = "-1";
    int number = ft_atoi(number_string);
    // char *encoding = decimal_to_hex(number, 4);
    char *encoding = decimal_to_hex_mk2(number, 4);
    ft_printf("%s\n", encoding);

    // unsigned int n = 15;
    // char *string = ft_itoa_base_local(n, 16);
    // ft_printf("%s\n", string);

    return (0);
}