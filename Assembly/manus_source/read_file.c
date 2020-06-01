#include "function_prototypes.h"


static void process_comment_char(t_container *container, t_buffer *buffer, char current_char)
{
    if (buffer->mode == regular)
    {
        current_char = skip_to_char(container->file_descriptor, '\n');
        add_to_buffer(buffer, current_char);
        append_buffer_to_tokens(container, buffer);
    }
    else if (buffer->mode == inside_string)
        add_to_buffer(buffer, current_char);
}

static void process_quote_char(t_container *container, t_buffer *buffer, char current_char)
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

static void process_separators(t_container *container, t_buffer *buffer, char current_char)
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

static void process_spaces(t_container *container, t_buffer *buffer, char current_char)
{
    if (buffer->mode == regular)
        append_buffer_to_tokens(container, buffer);
    else if (buffer->mode == inside_string)
        add_to_buffer(buffer, current_char);
}

void read_file(t_container *container)
{
    t_buffer *buffer;
    char current_char;

    buffer = new_buffer(BUFFER_SIZE);
    while ((current_char = get_char(container->file_descriptor)) != -1)
    {
        if (is_a_member(g_comment_chars, current_char))
            process_comment_char(container, buffer, current_char);
        else if (current_char == '"')
            process_quote_char(container, buffer, current_char);
        else if (is_a_member(g_spaces, current_char))
            process_spaces(container, buffer, current_char);
        else if (current_char == '\n' || current_char == SEPARATOR_CHAR)
            process_separators(container, buffer, current_char);
        else if(!ft_isascii(current_char))
            invoke_error("non ascii char\n", NULL, NULL, container); //msg
        else if (current_char == '\0')
            invoke_error("null character", NULL, NULL, container); //msg
        else
            add_to_buffer(buffer, current_char);
        if (buffer->status == red)
            invoke_error("buffer overflow\n", NULL, NULL, container); //msg
    }
    append_buffer_to_tokens(container, buffer);
    destroy_buffer(&buffer);
}