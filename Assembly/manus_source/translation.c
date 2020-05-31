#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"

struct s_translation *new_translation(void)
{
    struct s_translation *translation;

    translation = mallokill(sizeof(struct s_translation));
    translation->champ_name = NULL;
    translation->champ_comment = NULL;
    translation->exec_code = NULL;

    return (translation);
}

void destroy_translation(t_translation **translation)
{
    
    //
    // display_all_tokens((*translation)->champ_comment);
    // exit(1);
    //
    destroy_generic_list(&(*translation)->champ_name, NULL);
    destroy_generic_list(&(*translation)->champ_comment, NULL);
    destroy_generic_list(&(*translation)->exec_code, NULL);
    free(*translation);
    *translation = NULL;
}

t_generic_list *concatenate_translation(const struct s_translation *translation)
{
    t_generic_list *resulting_list;
    t_generic_list *last_in_name;
    t_generic_list *last_in_comment;

    // //
    // display_byte_strings(translation->champ_name);
    // ft_printf("%s", "\n");
    //

    last_in_name = get_last_element(translation->champ_name);
    last_in_comment = get_last_element(translation->champ_comment);
    resulting_list = translation->champ_name;
    resulting_list = concatenate_lists(resulting_list, translation->champ_comment, last_in_name);
    resulting_list = concatenate_lists(resulting_list, translation->exec_code, last_in_comment);

    return (resulting_list);
}

t_generic_list *translate_champ_comment(t_generic_list *current_token,
t_container *container)
{
    t_generic_list *translation;
    t_generic_list *last_element;
    t_generic_list *byte_string;


    translation = encode_string((t_token *)current_token->stuff);
    last_element = get_last_element(translation);

    //REMAINING BYTES
    if (container->parameters->comment_size > COMMENT_LENGTH)
        invoke_error("champ comment is too long;", (t_token *)current_token->stuff, NULL, container);
    byte_string = get_null_padding(COMMENT_LENGTH - container->parameters->comment_size);
    translation = concatenate_lists(translation, byte_string, last_element);
    last_element = get_last_element(byte_string);

    //PADDING
    byte_string = get_null_padding(PADDING_SIZE);
    translation = concatenate_lists(translation, byte_string, last_element);

    return (translation);
}

t_generic_list *translate_champ_name(t_generic_list *current_token,
t_container *container)
{
    t_generic_list *translation;
    t_generic_list *byte_string;
    t_generic_list *last_element;
    int name_length;

    name_length = 0;
    translation = encode_string((t_token *)current_token->stuff);
    last_element = get_last_element(translation);

    //REMAINING BYTES
    if (name_length > PROG_NAME_LENGTH)
        invoke_error("champ name is too long;", (t_token *)current_token->stuff, NULL, container);
    byte_string = get_null_padding(PROG_NAME_LENGTH - container->parameters->name_size); //is this right?
    translation = concatenate_lists(translation, byte_string, last_element);
    last_element = get_last_element(byte_string);

    //PADDING
    byte_string = get_null_padding(PADDING_SIZE);
    translation = concatenate_lists(translation, byte_string, last_element);
    last_element = get_last_element(byte_string);

    //EXEC CODE SIZE
    byte_string = new_generic_list(decimal_to_hex_mk2(container->parameters->exec_code_size, 4));
    translation = concatenate_lists(translation, byte_string, last_element);

    return (translation);
}

int get_arg_count(t_generic_list *token)
{
    t_generic_list *current_token;
    t_token *current_token_cast;
    int arg_count;

    arg_count = 0;
    current_token = token->next;

    while (1)
    {
        if (!current_token)
            return (arg_count);
        current_token_cast = (t_token *)current_token->stuff;
        if (current_token_cast->type == comma)
            current_token = current_token->next;
        else if (current_token_cast->type == argument)
        {
            arg_count ++;
            current_token = current_token->next;
        }
        else
            break ;
    }
    return (arg_count);
}

void compare_arg_counts(t_generic_list *token, t_container *container)
{
    t_token *token_cast;
    enum e_operation_name operation_name;
    int arg_count;

    token_cast = (t_token *)token->stuff;
    operation_name = get_operation_name(token_cast);
    arg_count = get_arg_count(token);
    if (op_tab[operation_name].arg_count != arg_count)
        invoke_error("wrong number of arguments for token\n", token_cast, NULL, container);
}

int get_operation_code(t_token *token)
{
    int value;
    int n;
    enum e_operation_name operation_name;

    operation_name = get_operation_name(token);
    value = 0;
    n = 0;
    while (n < op_tab[operation_name].arg_count)
    {
        value = (value | op_tab[operation_name].arg_type[n]);
        n ++;
    }
    return (value);
}

void compare_arg_type(t_token *previous_operation, t_token *current_token, t_container *container)
{
    unsigned int table_value;

    if (!previous_operation)
        invoke_error("unexpected error\n", NULL, NULL, container); //msg
    table_value = get_operation_code(previous_operation);
    if (table_value != (table_value | current_token->argument_type))
        invoke_error ("argument type mismatch\n", previous_operation, NULL, container); //msg
}

t_generic_list *translate_tokens(t_container *container)
{
    t_generic_list *current_token;
    t_generic_list *token_translation;
    t_generic_list *last_element;
    struct s_translation *translation;
    //
    t_token *current_token_cast;
    t_token *previous_operation = NULL;
    //
    translation = container->translation;
    last_element = NULL;
    current_token = container->tokens;
    while (current_token)
    {
        current_token_cast = (t_token *)current_token->stuff;

        if (((t_token *)current_token->stuff)->type == champ_name)
            translation->champ_name = translate_champ_name(current_token, container);
        else if (((t_token *)current_token->stuff)->type == champ_comment)
            translation->champ_comment = translate_champ_comment(current_token, container);
        else if (((t_token *)current_token->stuff)->type == operation)
        {
            compare_arg_counts(current_token, container);
            previous_operation = (t_token *)current_token->stuff;
            token_translation = encode_operation((t_token *)current_token->stuff);
            translation->exec_code = concatenate_lists(translation->exec_code, token_translation, last_element);
            last_element = token_translation;
            if (op_tab[get_operation_name((t_token *)current_token->stuff)].arg_code_flag)
            {
                token_translation = encode_type(current_token);
                translation->exec_code = concatenate_lists(translation->exec_code, token_translation, last_element);
                last_element = token_translation;
            }
        }
        else if (((t_token *)current_token->stuff)->type == argument)
        {
            compare_arg_type(previous_operation, (t_token *)current_token->stuff, container);
            token_translation = encode_argument(current_token, container->tokens, container);
            translation->exec_code = concatenate_lists(translation->exec_code, token_translation, last_element);
            last_element = token_translation;
        }
        current_token = current_token->next;
    }
    return (concatenate_translation(translation));
}