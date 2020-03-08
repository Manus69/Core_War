#include "tokens.h"
#include "function_prototypes.h"
#include "operation_table.h"

int get_absolute_distance_to_the_label(t_token *token, char *label_name, t_generic_list *labels)
{
    t_generic_list *current_token;
    char *substring;
    
    t_token *debug_token;

    current_token = labels;
    while (current_token)
    {

        debug_token = (t_token *)current_token->stuff;

        substring = ft_strsub(label_name, 0, ft_strlen(label_name) - 1);
        if (ft_strcmp(((t_token *)current_token->stuff)->string, substring) == 0)
            return (((t_token *)current_token->stuff)->distance - token->distance);
        free(substring);
        current_token = current_token->next;
    }
    return (-1);
}

int get_distance_to_the_previous_operation(t_token *token, t_generic_list *token_list) //returns a positive number;
{
    t_generic_list *current_token;
    t_token *previous_operation;

    current_token = token_list;
    previous_operation = NULL;
    while (current_token)
    {
        if (((t_token *)current_token->stuff)->type == operation)
        {
            if (((t_token *)current_token->stuff)->distance < token->distance)
                previous_operation = ((t_token *)current_token->stuff);
            else
                break ;
        }
        current_token = current_token->next;
    }
    if (!previous_operation)
        return (-1);
    return (token->distance - previous_operation->distance);
}

int get_distance_to_the_next_operation(t_generic_list *token)
{
    t_generic_list *current_token;
    int distance;

    current_token = token;
    distance = -1;
    while (current_token)
    {
        if (((t_token *)current_token->stuff)->type == operation)
        {
            distance = ((t_token *)current_token->stuff)->distance - ((t_token *)token->stuff)->distance;
            break ;
        }
        current_token = current_token->next;
    }
    return (distance);
}

int get_distance_to_the_label(t_generic_list *token, char *label_name, t_generic_list *tokens, t_generic_list *labels)
{
    int absolute_distance;
    int distance_to_the_previous_operation;
    int distance_to_the_next_operation;
    t_token *current_token;

    current_token = ((t_token *)token->stuff);
    absolute_distance = get_absolute_distance_to_the_label(current_token, label_name, labels);
    if (absolute_distance < 0)
    {
        distance_to_the_previous_operation = get_distance_to_the_previous_operation(current_token, tokens);
        if (distance_to_the_previous_operation < 0)
            invoke_error("this is broken!");
        return (absolute_distance + distance_to_the_previous_operation);
    }
    else
    {
        // distance_to_the_next_operation = get_distance_to_the_next_operation(token);
        
        // if (distance_to_the_next_operation < 0)
        //     invoke_error("does not work!");
        distance_to_the_previous_operation = get_distance_to_the_previous_operation(current_token, tokens);
        if (distance_to_the_previous_operation < 0)
            invoke_error("this is broken!");
        return (absolute_distance - distance_to_the_previous_operation);
    }
}