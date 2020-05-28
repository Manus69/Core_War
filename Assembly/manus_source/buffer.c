#include "tokens.h"
#include "function_prototypes.h"


t_buffer *new_buffer(unsigned int size)
{
    t_buffer *buffer;

    buffer = mallokill(sizeof(struct s_buffer));
    buffer->content = ft_strnew(size);
    buffer->current_content_size = 0;
    buffer->max_content_size = size;
    buffer->mode = regular;

    return (buffer);
}

char *get_buffer_string(t_buffer *buffer)
{
    char *string;

    string = ft_strsub(buffer->content, 0, buffer->current_content_size);
    buffer->current_content_size = 0;

    return (string);
}

int add_to_buffer(t_buffer *buffer, char c)
{
    if (buffer->current_content_size == buffer->max_content_size)
    {
        invoke_error("buffer is full\n", NULL, NULL); //msg
        return (0);
    }
    if (c < 0)
    {
        invoke_error("forbidden character\n", NULL, &c); //msg
        return (0);
    }

    buffer->content[buffer->current_content_size] = c;
    buffer->current_content_size ++;

    return (1);
}

void append_buffer_to_tokens(t_container *container, t_buffer *buffer)
{
    t_token *token;

    if (buffer->current_content_size == 0)
        return ;
    token = new_token(get_buffer_string(buffer), 0);
    container->tokens = add_to_list(container->tokens, token);
}