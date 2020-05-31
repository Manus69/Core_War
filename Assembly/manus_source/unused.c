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


t_generic_list *encode_string_tokens(t_generic_list *tokens)
{
    t_generic_list *current_token;
    t_generic_list *encoding;
    t_generic_list *string_encoding;
    t_generic_list *last_element;

    current_token = tokens;
    encoding = NULL;
    last_element = NULL;
    while (((t_token *)current_token->stuff)->type == string)
    {
        string_encoding = encode_string((t_token *)current_token->stuff);
        encoding = concatenate_lists(encoding, string_encoding, last_element);
        last_element = get_last_element(string_encoding);
        current_token = current_token->next;
        if (((t_token *)current_token->stuff)->type == string)
        {
            last_element = add_to_list(last_element, ft_itoa_base(' ', NUMBER_SYSTEM_BASE));
            last_element = last_element->next;
        }
    }
    return (encoding);
}


void set_token_size(t_token *token) //this will not work, since arg size varies depending on the operation ffs
{
    enum e_operation_name operation_type;

    if (token->type == string)
        token->size = ft_strlen(token->string);
    else if (token->type == operation)
    {
        operation_type = get_operation_name(token);
        if (op_tab[operation_type].arg_code_flag == 1)
            token->size = 2;
        else
            token->size = 1;
    }
    else if (token->type == argument)
    {
        if (token->argument_type == registry)
            token->size = REG_ARG_SIZE;
        else if (token->argument_type == direct)
            token->size = DIR_ARG_SIZE;
        else if (token->argument_type == indirect)
            token->size = IND_ARG_SIZE;
    }
}

int get_next_index(const char *string, int start, const char *char_set)
{
    int n;

    n = start;
    while (string[n] != '\0')
    {
        if (is_a_member(char_set, string[n]))
            return (n);
        n = n + 1;
    }

    //to avoid error checking;
    invoke_error("string parsing errror\n", NULL, string, NULL);
    //

    return (-1);
}

char *get_next_substring(const char *string, int *start,
const char *start_char_set, const char *end_char_set)
{
    int m;
    int n;
    char *substring;

    m = get_next_index(string, *start, start_char_set);
    n = get_next_index(string, m + 1, end_char_set);
    substring = ft_strsub(string, m, n - m);
    *start = n;
    return (substring);
}