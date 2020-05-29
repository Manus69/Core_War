void check_terminator(int file_descriptor)
{
    char buffer[1];

    lseek(file_descriptor, -1, SEEK_END);
    read(file_descriptor, buffer, 1);
    if (buffer[0] != '\n')
        invoke_error("no newline at the end of file\n", NULL, NULL);
    lseek(file_descriptor, 0, SEEK_SET);
}

void check_last_character(int file) //should not be used
{
    char c;

    lseek(file, -1, SEEK_END);
    read(file, &c, 1);
    if (c != '\n')
        invoke_error("the file does not end with the new line\n", NULL, NULL);
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


t_token *get_next_token(int *n, char *line)
{
    int m;
    t_token *token;
    char *substring;

    token = NULL;
    m = *n;
    if (line[*n] == '"')
    {        
        while (line[m] != '\0')
        {
            m = m + 1;
            if (line[m] == '"')
            {
                m = m + 1;
                break ;
            } 
        }
    }
    else if (is_a_member(g_separators, line[*n]))
    {
        substring = ft_strsub(line, *n, 1);
        token = new_token(substring, 0);
        *n = *n + 1;
        return (token);
    }
    else
    {
        while (line[m] != '\0' && !is_a_member(g_separators, line[m]) && !is_a_member(g_spaces, line[m]))
        {
            m = m + 1;
        }
    }
    if (m - *n > 0)
    {
        substring = ft_strsub(line, *n, m - *n);
        token = new_token(substring, 0);
    }
    *n = m;
    if (!token)
        token = new_token("NULL TOKEN", null);
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