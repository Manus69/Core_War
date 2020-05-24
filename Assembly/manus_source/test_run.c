#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"


const char *g_file_name; //used to pass filename between the files; use s_container instead? 

int read_header(int file, char *buffer) //assuming the buffer is allocated
{
    int number_of_quotes;
    int number_of_lines;
    int current_index;

    number_of_lines = 1;
    number_of_quotes = 0;
    current_index = 0;
    while (number_of_quotes < 4) //quote number invariant
    {
        if (read(file, &buffer[current_index], 1) <= 0)
            invoke_error("something is wrong with the header\n", NULL, NULL); //get the right message;
        
        if (buffer[current_index] == '"')
            number_of_quotes ++;
        else if (buffer[current_index] == '\n')
            number_of_lines ++;
        current_index ++;
    }
    return (number_of_lines);
}

//this has to check for invalid substrings in the header! 
t_generic_list *parse_header(const char *header)
{
    int n;
    char *string; //debug variable? 
    t_generic_list *token_list;

    token_list = NULL;
    n = 0;
    string = get_next_substring(header, &n, ".", "\t \"");
    token_list = add_to_list(token_list, new_token(string, 0));
    string = get_next_substring(header, &n, "\"", "\"");
    string = concat(string, "\""); //leak;
    n = n + 1;
    token_list = add_to_list(token_list, new_token(string, 0));

    token_list = add_to_list(token_list, new_token("\n", new_line));

    string = get_next_substring(header, &n, ".", "\t \"");
    token_list = add_to_list(token_list, new_token(string, 0));
    string = get_next_substring(header, &n, "\"", "\"");
    string = concat(string, "\""); //leak;
    n = n + 1;
    token_list = add_to_list(token_list, new_token(string, 0));

    return (token_list);
}

void header_to_tokens(const char *header, t_generic_list *tokens)
{
    ;
}

void lines_to_tokens(int file, t_generic_list *tokens)
{
    char *current_line;
    t_generic_list *line_tokens;
    t_generic_list *last_element;

    last_element = get_last_element(tokens);
    while (get_next_line(file, &current_line) > 0)
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
}

void translate_and_write_to_file(t_container *container, int visible)
{
    int file;
    t_generic_list *translation;
    t_generic_list *prefix_item;
    char *new_file_name;

    translation = translate_tokens(container);
    prefix_item = new_generic_list(ft_strdup("00ea83f3"));
    prefix_item = concatenate_lists(prefix_item, translation, NULL);

    if (visible)
    {
        display_byte_strings(prefix_item);
        // return ;
    }

    new_file_name = trim_file_name(g_file_name);
    new_file_name = replace_extension(new_file_name);  //leak;
    file = open(new_file_name, O_RDWR | O_CREAT, 0777);
    if (file < 0)
        invoke_error("open / create failure", NULL, NULL); // EMSG
    tokens_to_bytes(prefix_item, file); //change for a suitable file descriptor;
    ft_printf("Writing output program to %s\n", new_file_name); //make a string constant message?
    close(file);
}

//where are the files supposed to go if one runs the pogramme from a different directory?
//remove the file that might have been created after the error invocation;
//ft_itoa_base from libft is shit;
//make an overarching structure for input and lists or something;

//header must be checked during parsing; fuck (#.name ... .name ) etc;
//.name and .comment can change places
//clean up the structs and grammar
//empty champ name? 
//double label: \n label2 ?

//disassmbler crashed on some input
//add argument type checks!
//retarder label names? :label: ? 

//transcription parameters do no work when comment and name come in reverse order
//get rid of string and quotation mark tokens? 
//do i need to check the file size?
//header has problems with #
//quote number invariant might be wrong: # "" ? 

void here_we_go(char *file_name)
{
    char *buffer;
    t_container *container;

    container = new_container(file_name);
    //
    g_file_name = file_name; //used in invoke error calls
    //

    buffer = ft_strnew(HEADER_BUFFER_SIZE);
    read_header(container->file_descriptor, buffer);
    // ft_printf("%s %d", buffer, number_of_header_lines);

    container->tokens = parse_header(buffer);
    lines_to_tokens(container->file_descriptor, container->tokens);
    close(container->file_descriptor);
    //
    // display_all_tokens(tokens);
    // exit(1);
    //
    
    classify_all_tokens(container->tokens, &container->labels, 1);
    measure_token_size(container->tokens);
    set_global_distance(container);
    //
    // display_all_tokens(container->tokens);
    // exit(1);
    //
    get_transcription_parameters(container);
    translate_and_write_to_file(container, 0);
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