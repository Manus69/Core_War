#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"
#include <fcntl.h>

const char *g_file_name; //used to pass filename between the files;

unsigned int measure_file_size(int file)
{
    unsigned int size;
    char buffer[1];

    size = 0;
    while (read(file, buffer, 1))
        size ++;
    return (size);
}

char get_last_char(int file) //make one function for this and file size if you really need it
{
    unsigned int n;
    char buffer[1];

    n = 0;
    while (read(file, buffer, 1))
        ;
    return (buffer[0]);
}

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

void check_terminator(const char *file_name)
{
    int file;
    char last_char;

    file = open(file_name, O_RDONLY);
    if (file < 0)
        invoke_error(FILE_ERROR_MESSAGE, NULL, NULL);
    
    last_char = get_last_char(file);
    if (last_char != '\n')
        invoke_error("no newline at the end of file\n", NULL, NULL);
    close(file);
}


void translate_and_write_to_file(t_generic_list *tokens, t_generic_list *labels,
t_transcription_parameters *transcription_parameters, int visible)
{
    int file;
    t_generic_list *translation;
    t_generic_list *prefix_item;
    char *new_file_name;

    translation = translate_tokens(tokens, labels, transcription_parameters);
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
//translation of comment lenght is wrong

//disassmbler crashed on some input
//add argument type checks!

// gobepc:	st r1, :buff
// 	ld :buff,r1
// buff:	st r1,r1	

void here_we_go(char *file_name)
{
    int file;
    char *buffer;
    t_transcription_parameters *transcription_parameters;
    t_generic_list *tokens;
    t_generic_list *labels;

    //
    g_file_name = file_name;
    //
    check_terminator(file_name);
    file = open(file_name, O_RDONLY);
    if (file < 0)
        invoke_error(FILE_ERROR_MESSAGE, NULL, NULL);

    buffer = ft_strnew(HEADER_BUFFER_SIZE);
    read_header(file, buffer);
    // ft_printf("%s %d", buffer, number_of_header_lines);

    //
    tokens = NULL;
    tokens = parse_header(buffer);
    lines_to_tokens(file, tokens);
    close(file);
    //
    // display_all_tokens(tokens);
    // exit(1);
    //
    
    labels = NULL;
    classify_all_tokens(tokens, &labels, 1);
    measure_token_size(tokens);
    set_global_distance(tokens);
    //
    // display_all_tokens(tokens);
    //
    transcription_parameters = get_transcription_parameters(tokens);
    translate_and_write_to_file(tokens, labels, transcription_parameters, 0);
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