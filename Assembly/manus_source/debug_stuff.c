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
    // const char *number_string = "4278415366";
    // int number = ft_atoi(number_string);
    // char *encoding = decimal_to_hex_mk2(number, 4);
    // ft_printf("%s\n", encoding);

    const char *number = "-101";
    long n = why_atol(number);
    ft_printf("%ld\n", n);

    return (0);
}