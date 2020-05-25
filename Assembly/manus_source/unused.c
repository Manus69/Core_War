void check_terminator(int file_descriptor)
{
    char buffer[1];

    lseek(file_descriptor, -1, SEEK_END);
    read(file_descriptor, buffer, 1);
    if (buffer[0] != '\n')
        invoke_error("no newline at the end of file\n", NULL, NULL);
    lseek(file_descriptor, 0, SEEK_SET);
}

void lines_to_tokens(t_container *container)
{
    char *current_line;
    t_generic_list *line_tokens;
    t_generic_list *last_element;

    // last_element = get_last_element(container->tokens);
    last_element = NULL;
    while (get_next_line(container->file_descriptor, &current_line) > 0)
    {
        line_tokens = line_to_tokens(current_line);
        if (line_tokens)
        {
            container->tokens = concatenate_lists(container->tokens, line_tokens, last_element);
            last_element = get_last_element(line_tokens);
            last_element = add_to_list(last_element, new_token("\n", new_line));
            last_element = last_element->next;
        }
        else if (!line_tokens && !container->tokens)
        {
            container->tokens = new_generic_list(new_token("\n", new_line));
            last_element = container->tokens;
        }
        else if (!line_tokens)
        {
            container->tokens = concatenate_lists(container->tokens, new_generic_list(new_token("\n", new_line)), last_element);
            last_element = last_element->next;
        }
        free(current_line);
    }
}