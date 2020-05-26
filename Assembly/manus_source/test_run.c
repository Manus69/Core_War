#include "ft_printf.h"
#include "libft.h"
#include "op.h"
#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"


const char *g_file_name;

void read_file(t_container *container)
{
    t_buffer *buffer;
    char current_char;

    buffer = new_buffer(BUFFER_SIZE);
    while ((current_char = get_char(container->file_descriptor)) != -1)
    {
        if (is_a_member(g_comment_chars, current_char))
        {
            if (buffer->mode == regular)
                skip_to_char(container->file_descriptor, '\n');
            else if (buffer->mode == inside_string)
                add_to_buffer(buffer, current_char);
        }
        else if (current_char == '"')
        {
            if (buffer->mode == regular)
            {
                append_buffer_to_tokens(container, buffer);
                add_to_buffer(buffer, current_char);
                buffer->mode = inside_string;
            }
            else if (buffer->mode == inside_string)
            {
                add_to_buffer(buffer, current_char);
                append_buffer_to_tokens(container, buffer);
                buffer->mode = regular;
            }
        }
        else if (is_a_member(g_spaces, current_char))
        {
            if (buffer->mode == regular)
                append_buffer_to_tokens(container, buffer);
            else if (buffer->mode == inside_string)
                add_to_buffer(buffer, current_char);
        }
        else if (current_char == '\n' || current_char == SEPARATOR_CHAR)
        {
            if (buffer->mode == regular)
            {
                append_buffer_to_tokens(container, buffer);
                add_to_buffer(buffer, current_char);
                append_buffer_to_tokens(container, buffer);
            }
            else if (buffer->mode == inside_string)
                add_to_buffer(buffer, current_char);
        }
        else
            add_to_buffer(buffer, current_char);
    }
    append_buffer_to_tokens(container, buffer);
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

//.name and .comment can change places
//clean up the structs and grammar
//empty champ name? 
//double label: \n label2 ?

//disassmbler crashed on some input
//add argument type checks!
//retarder label names? :label: ? 

//do i need to check the file size?

void here_we_go(char *file_name)
{
    // char *buffer;
    t_container *container;

    container = new_container(file_name);
    //
    g_file_name = file_name; //used in invoke error calls
    //

    read_file(container);
    close(container->file_descriptor);
    //
    // display_all_tokens(container->tokens);
    // exit(1);
    //

    classify_all_tokens(container);
    //
    // display_all_tokens(container->tokens);
    // exit(1);
    //
    measure_token_size(container->tokens);
    set_global_distance(container);
    //
    // display_all_tokens(container->tokens);
    // exit(1);
    //
    get_transcription_parameters(container);
    translate_and_write_to_file(container, 0);
}
