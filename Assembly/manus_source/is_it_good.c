#include "function_prototypes.h"

int     is_command(char *string)
{
    return (is_string_in_array(string, g_command_names));
}

int     is_command_name(char *string)
{
    if (ft_strcmp(string, g_command_names[0]) == 0)
        return (1);
    return (0);
}

int     is_command_comment(char *string)
{
    if (ft_strcmp(string, g_command_names[1]) == 0)
        return (1);
    return (0);
}

int     is_string(char *string)
{
    int length;

    length = ft_strlen(string);
    if (string[0] == '"')
    {
        if (string[length - 1] == '"')
            return (1);
    }
    return (0);
}