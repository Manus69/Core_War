#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"
#include <fcntl.h>

t_token *new_token(char *string, enum e_token_type type)
{
    t_token *token;

    token = mallokill(sizeof(t_token));
    token->string = string;
    if (type == 0)
        token->type = unknown;
    else
        token->type = type;
    token->argument_type = not_applicable;
    token->size = 0;
    token->distance = -1;
    return (token);
}

t_token *get_next_token(int *n, char *line)
{
    int m;
    t_token *token;
    char *substring;
    char test;

    token = NULL;
    //
    test = line[*n];
    //
    if (is_a_member(g_separators, line[*n]))
    {
        substring = ft_strsub(line, *n, 1);
        token = new_token(substring, 0);
        *n = *n + 1;
        return (token);
    }
    m = *n;
    while (line[m] != '\0' && !is_a_member(g_separators, line[m]) && !is_a_member(g_spaces, line[m]))
    {
        test = line[m];
        m = m + 1;
    }
    if (m - *n > 0)
    {
        substring = ft_strsub(line, *n, m - *n);
        token = new_token(substring, 0);
    }
    *n = m;
    return (token);
}

t_generic_list *line_to_tokens(char *line)
{
    int n;
    t_token *token;
    t_generic_list *token_list;

    n = 0;
    token = NULL;
    token_list = NULL;
    while (line[n] != '\0')
    {
        while (is_a_member(g_spaces, line[n]))
            n = n + 1;
        token = get_next_token(&n, line);
        //
        // display_token(token);
        //
        token_list = add_to_list(token_list, token);
    }
    return (token_list);
}

void classify_token(t_token *current_token, t_token *previous_token, int verbose)
{
    if (!current_token)
        return ;
    if (previous_token == NULL)
    {
        if (is_command(current_token->string))
            current_token->type = command;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == new_line)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_label(current_token->string))
            current_token->type = label;
        else if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (is_operation(current_token->string))
            current_token->type = operation;
        else if (is_command(current_token->string))
            current_token->type = command;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == command)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = opening_quotation_mark;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == label)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else if (is_operation(current_token->string))
            current_token->type = operation;
        else if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == operation)
    {
        if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (check_argument_token(current_token))
            ;
        else if (is_new_line(current_token->string)) //is this legal?
            current_token->type = new_line;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == argument)
    {
        if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (is_argument_separator(current_token->string))
            current_token->type = comma;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == comma)
    {
        if (is_comment_character(current_token->string))
            current_token->type = hashtag;
        else if (check_argument_token(current_token))
            ;
        else
            display_classification_error_message(current_token, verbose);
    }
    else if (previous_token->type == hashtag)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            current_token->type = comment;
    }
    else if (previous_token->type == comment)
    {
        if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            current_token->type = comment;
    }
    else if (previous_token->type == opening_quotation_mark)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = closing_quotation_mark;
        else
            current_token->type = string;
    }
    else if (previous_token->type == closing_quotation_mark)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = opening_quotation_mark;
        else if (is_new_line(current_token->string))
            current_token->type = new_line;
        else
            display_classification_error_message(current_token, verbose);
        
    }
    else if (previous_token->type == string)
    {
        if (is_quotation_mark(current_token->string))
            current_token->type = closing_quotation_mark;
        else
            current_token->type = string;
    }
    // set_token_size(current_token);
}

void classify_all_tokens(t_generic_list *tokens, t_generic_list **labels, int verbose)
{
    t_token *current_token;
    t_token *previous_token;
    t_generic_list *current_item;

    previous_token = NULL;
    current_item = tokens;
    while (current_item)
    {
        if (!current_item->stuff)
            invoke_error("a token is bricked!");
            // break ;
        current_token = current_item->stuff;
        classify_token(current_token, previous_token, verbose);
        if (current_token->type == label)
            *labels = add_to_list(*labels, current_token);
        current_item = current_item->next;
        previous_token = current_token;
    }
}

t_generic_list *translate_tokens(t_generic_list *tokens, t_generic_list *labels)
{
    t_generic_list *translation;
    t_generic_list *current_token;
    t_generic_list *current_token_translation;
    t_generic_list *last_element;
    t_token *current_token_cast;
    int bytes_encoded;

    char *debug_string;

    translation = NULL;
    last_element = NULL;
    bytes_encoded = 0;
    current_token = tokens;
    if (!current_token)
        invoke_error("empty token list");
    while (current_token)
    {
        current_token_cast = (t_token *)current_token->stuff;
        if (current_token_cast->type == string)
        {
            current_token_translation = encode_string(current_token_cast, &bytes_encoded);
            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = current_token_translation;
        }
        else if (current_token_cast->type == operation)
        {
            current_token_translation = encode_operation(current_token_cast, &bytes_encoded);

            debug_string = current_token_translation->stuff;

            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = current_token_translation;
            if (op_tab[get_operation_name(current_token_cast)].arg_code_flag)
            {
                current_token_translation = encode_type(current_token, &bytes_encoded);

                debug_string = current_token_translation->stuff;

                translation = concatenate_lists(translation, current_token_translation, last_element);
                last_element = current_token_translation;
            }
        }
        else if (current_token_cast->type == argument)
        {
            current_token_translation = encode_argument(current_token, tokens, labels, &bytes_encoded);

            debug_string = current_token_translation->stuff;

            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = current_token_translation;
        }
        current_token = current_token->next;
    }
    return (translation);
}



//string separators are lost during tokenization;
//is it necessary to check for large (more than two bytes) numbers?
//the size constants are all fucked up!

//printf and libft makefiles are fucked up? 

//make sure that all addressing is done mod mem_size;
//apply modulus for indirect arguments;

int main()
{
    char *current_line;
    int file;
    t_generic_list *tokens;
    t_generic_list *line_tokens;
    t_generic_list *last_element;
    t_generic_list *labels;

    char *file_name = "test_file.s";

    file = open(file_name, O_RDONLY);

    // file = open("/home/anus/projects/core_war/Assembly/test_champ.s", O_RDONLY);
    // file = open("/home/anus/projects/core_war/Assembly/test_file.s", O_RDONLY);
    // file = open("/home/anus/projects/core_war/Resources/champs/42.s", O_RDONLY);
    if (file < 0)
    {
        ft_printf("%s", FILE_ERROR_MESSAGE);
        exit(1);
    }
    tokens = NULL;
    last_element = NULL;
    while (get_next_line(file, &current_line) > 0) //careful about the trailing \n; the thing is fucked up;
    {
        line_tokens = line_to_tokens(current_line);
        if (line_tokens)
        {
            tokens = concatenate_lists(tokens, line_tokens, last_element);
            last_element = get_last_element(line_tokens);
            last_element = add_to_list(last_element, new_token("\n", new_line));
            last_element = last_element->next;
        }
        else if (!line_tokens && !tokens)
        {
            tokens = new_generic_list(new_token("\n", new_line));
            last_element = tokens;
        }
        else if (!line_tokens)
        {
            tokens = concatenate_lists(tokens, new_generic_list(new_token("\n", new_line)), last_element);
            last_element = last_element->next;
        }
        free(current_line);
    }
    labels = NULL;
    classify_all_tokens(tokens, &labels, 1);
    measure_token_size(tokens);
    set_global_distance(tokens);
    display_all_tokens(tokens);
    // display_all_tokens(labels);

    t_generic_list *translation = translate_tokens(tokens, labels);
    display_byte_strings(translation);

    //TESTING AREA

    char *byte_string = grab_n_bytes_from_address(tokens, 0, 10);
    // ft_printf("\n%s\n", byte_string);

    t_generic_list *encoding;
    int bytes_encoded = 0;
    t_generic_list *current_token = tokens;
    
    t_token *test_token1 = new_token("r1", argument);
    test_token1->argument_type = registry;
    t_token *test_token2 = new_token("?", argument);
    test_token2->argument_type = direct;
    t_token *test_token3 = new_token("?", argument);
    test_token3->argument_type = direct;
    char *argument_encoding = get_type_encoding(3, test_token1, test_token2, test_token3);

    t_token *op_token = new_token("sti", operation);
    t_generic_list *argument_test = new_generic_list(op_token);
    argument_test = add_to_list(argument_test, test_token1);
    argument_test = add_to_list(argument_test, test_token2);
    argument_test = add_to_list(argument_test, test_token3);
    t_generic_list *encoding_test = encode_type(argument_test, &bytes_encoded);
    // display_byte_strings(encoding_test);

    // ft_printf(get_direct_number_encoding(new_token("%2", argument)));
    // display_byte_strings(encoding);
    //

    return (0);
}