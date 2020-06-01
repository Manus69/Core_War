#include "function_prototypes.h"

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
    free(pad_string);

    return (result);
}

int     is_string_in_array(char *string, char **string_array)
{
    int n;
    char *current_string;

    n = 0;
    current_string = string_array[0];
    while (current_string)
    {
        if (ft_strcmp(current_string, string) == 0)
            return (1);
        n = n + 1;
        current_string = string_array[n];
    }
    return (0);
}