#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"
#include <fcntl.h>

const char *g_file_name;

char *replace_extension(const char *file_name)
{
    unsigned int length;
    char *replacing_string;

    if (ft_strlen(file_name) < 3)
        invoke_error("file name error", NULL, NULL); //EMSG
    length = ft_strlen(file_name) + 2;
    replacing_string = ft_strnew(length);
    replacing_string = ft_strcpy(replacing_string, file_name);
    replacing_string[length - 3] = 'c';
    replacing_string[length - 2] = 'o';
    replacing_string[length - 1] = 'r';
    return (replacing_string);
}

char *trim_file_name(const char *file_name)
{
    unsigned int length;
    char *resulting_string;
    int slash_index;

    length = ft_strlen(file_name);
    if (length < 3)
        invoke_error("file name error while trimmig", NULL, NULL); //EMSG
    slash_index = is_in_string(file_name, '/'); //define a macro for this!
    if (slash_index == -1)
        return (ft_strdup(file_name));
    resulting_string = ft_strsub(file_name, slash_index + 1, length - slash_index - 1);
    return (resulting_string);
}

//.name "..." .name "..." ... is considered valid now?
//is it necessary to check for large (more than two bytes) numbers?
//the size constants are all fucked up!
//add support for ; character;
//where are the files supposed to go if one runs the pogramme from a different directory?
//remove the file that might have been created after the error invocation;
//ft_itoa_base from libft is shit;

void here_we_go(char *file_name)
{
    char *current_line;
    int file;
    t_transcription_parameters *transcription_parameters;
    t_generic_list *tokens;
    t_generic_list *line_tokens;
    t_generic_list *last_element;
    t_generic_list *labels;

    file = open(file_name, O_RDONLY);
    if (file < 0)
    {
        ft_printf("%s", FILE_ERROR_MESSAGE);
        exit(1);
    }

    //
    g_file_name = file_name;
    //

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
    close(file);
    labels = NULL;
    //
    // display_all_tokens(tokens);
    //
    classify_all_tokens(tokens, &labels, 1);
    measure_token_size(tokens);
    set_global_distance(tokens);
    //
    // display_all_tokens(tokens);
    //
    transcription_parameters = get_transcription_parameters(tokens);

    //string translation is FUCKED UP;
    t_generic_list *translation = translate_tokens(tokens, labels, transcription_parameters);
    //
    char *prefix = ft_strdup("00ea83f3"); //fix it later;
    t_generic_list *prefix_item = new_generic_list(prefix);
    prefix_item = concatenate_lists(prefix_item, translation, NULL);
    //
    // display_byte_strings(prefix_item);
    //
    char *new_file_name = trim_file_name(file_name);
    new_file_name = replace_extension(new_file_name);  //leak;
    file = open(new_file_name, O_RDWR | O_CREAT, 0777);
    if (file < 0)
        invoke_error("open / create failure", NULL, NULL); // EMSG
    tokens_to_bytes(prefix_item, file); //change for a suitable file descriptor;
}

// int main()
// {
//     char *current_line;
//     int file;
//     t_generic_list *tokens;
//     t_generic_list *line_tokens;
//     t_generic_list *last_element;
//     t_generic_list *labels;

//     char *file_name = "test_champ.s";
//     // char *file_name = "test_file.s";

//     file = open(file_name, O_RDONLY);

//     // file = open("/home/anus/projects/core_war/Assembly/test_champ.s", O_RDONLY);
//     // file = open("/home/anus/projects/core_war/Assembly/test_file.s", O_RDONLY);
//     // file = open("/home/anus/projects/core_war/Resources/champs/42.s", O_RDONLY);
//     if (file < 0)
//     {
//         ft_printf("%s", FILE_ERROR_MESSAGE);
//         exit(1);
//     }
//     tokens = NULL;
//     last_element = NULL;
//     while (get_next_line(file, &current_line) > 0) //careful about the trailing \n; the thing is fucked up;
//     {
//         line_tokens = line_to_tokens(current_line);
//         if (line_tokens)
//         {
//             tokens = concatenate_lists(tokens, line_tokens, last_element);
//             last_element = get_last_element(line_tokens);
//             last_element = add_to_list(last_element, new_token("\n", new_line));
//             last_element = last_element->next;
//         }
//         else if (!line_tokens && !tokens)
//         {
//             tokens = new_generic_list(new_token("\n", new_line));
//             last_element = tokens;
//         }
//         else if (!line_tokens)
//         {
//             tokens = concatenate_lists(tokens, new_generic_list(new_token("\n", new_line)), last_element);
//             last_element = last_element->next;
//         }
//         free(current_line);
//     }
//     labels = NULL;
//     classify_all_tokens(tokens, &labels, 1);
//     measure_token_size(tokens);
//     set_global_distance(tokens);
//     display_all_tokens(tokens);
//     // display_all_tokens(labels);

//     t_generic_list *translation = translate_tokens(tokens, labels);
//     ft_printf("%#x", COREWAR_EXEC_MAGIC);
//     display_byte_strings(translation);

//     //TESTING AREA

//     char *byte_string = grab_n_bytes_from_address(tokens, 0, 10);
//     // ft_printf("\n%s\n", byte_string);

//     t_generic_list *encoding;
//     int bytes_encoded = 0;
//     t_generic_list *current_token = tokens;
    
//     t_token *test_token1 = new_token("r1", argument);
//     test_token1->argument_type = registry;
//     t_token *test_token2 = new_token("?", argument);
//     test_token2->argument_type = direct;
//     t_token *test_token3 = new_token("?", argument);
//     test_token3->argument_type = direct;
//     char *argument_encoding = get_type_encoding(3, test_token1, test_token2, test_token3);

//     t_token *op_token = new_token("sti", operation);
//     t_generic_list *argument_test = new_generic_list(op_token);
//     argument_test = add_to_list(argument_test, test_token1);
//     argument_test = add_to_list(argument_test, test_token2);
//     argument_test = add_to_list(argument_test, test_token3);
//     t_generic_list *encoding_test = encode_type(argument_test, &bytes_encoded);
//     // display_byte_strings(encoding_test);

//     // ft_printf(get_direct_number_encoding(new_token("%2", argument)));
//     // display_byte_strings(encoding);
//     //

//     return (0);
// }