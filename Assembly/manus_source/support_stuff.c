#include "function_prototypes.h"

int is_a_member(char *set, char c)
{
    int n;

    n = 0;
    while (set[n] != '\0')
    {
        if (set[n] == c)
            return (1);
        n = n + 1;
    }
    return (0);
}