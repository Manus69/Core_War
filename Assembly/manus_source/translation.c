#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"

enum e_string_stranslation_mode
{
    champ_name_string,
    champ_comment_string,
};

struct s_translation
{
    t_generic_list *champ_name;
    t_generic_list *champ_comment;
    t_generic_list *exec_code;
};

struct s_translation *new_translation(void)
{
    struct s_translation *translation;

    translation = mallokill(sizeof(struct s_translation));
    translation->champ_name = NULL;
    translation->champ_comment = NULL;
    translation->exec_code = NULL;
    return (translation);
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
t_transcription_parameters *transcription_parameters, int *bytes_encoded)
{
    t_generic_list *translation;
    t_generic_list *last_element;
    t_generic_list *byte_string;


    translation = encode_string((t_token *)current_token->stuff, bytes_encoded);
    // translation = concatenate_lists(translation, current_token_translation, last_element);
    last_element = get_last_element(translation);

    //REMAINING BYTES
    if (transcription_parameters->comment_size > COMMENT_LENGTH)
        invoke_error("champ comment is too long;", (t_token *)current_token->stuff, NULL);
    byte_string = get_null_padding(COMMENT_LENGTH - transcription_parameters->comment_size); //this is constant; this cant be right
    translation = concatenate_lists(translation, byte_string, last_element);
    last_element = get_last_element(byte_string);

    //PADDING
    byte_string = get_null_padding(PADDING_SIZE);
    translation = concatenate_lists(translation, byte_string, last_element);
    // last_element = get_last_element(current_token_translation);

    return (translation);
}

t_generic_list *translate_champ_name(t_generic_list *current_token,
t_transcription_parameters *transcription_parameters, int *bytes_encoded)
{
    t_generic_list *translation;
    t_generic_list *byte_string;
    t_generic_list *last_element;
    int name_length;

    name_length = 0;
    translation = encode_string((t_token *)current_token->stuff, &name_length);
    // translation = concatenate_lists(translation, current_token_translation, last_element);
    last_element = get_last_element(translation);

    //REMAINING BYTES
    if (name_length > PROG_NAME_LENGTH)
        invoke_error("champ name is too long;", (t_token *)current_token->stuff, NULL);
    byte_string = get_null_padding(PROG_NAME_LENGTH - transcription_parameters->name_size); //is this right?
    translation = concatenate_lists(translation, byte_string, last_element);
    last_element = get_last_element(byte_string);

    //PADDING
    byte_string = get_null_padding(PADDING_SIZE);
    translation = concatenate_lists(translation, byte_string, last_element);
    last_element = get_last_element(byte_string);

    //EXEC CODE SIZE
    byte_string = new_generic_list(decimal_to_hex_mk2(transcription_parameters->exec_code_size, 4));
    translation = concatenate_lists(translation, byte_string, last_element);
    // last_element = get_last_element(current_token_translation);

    return (translation);
}

t_generic_list *translate_tokens(t_generic_list *tokens,
t_generic_list *labels, t_transcription_parameters *transcription_parameters)
{
    t_generic_list *current_token;
    t_generic_list *current_token_translation;
    t_generic_list *last_element;
    t_token *current_token_cast;
    int bytes_encoded;
    
    struct s_translation *translation;
    enum e_string_stranslation_mode string_translation_mode;

    //
    // ft_printf("%d %d %d\n", transcription_parameters->name_size, transcription_parameters->comment_size, transcription_parameters->exec_code_size);
    // exit(1);
    //

    translation = new_translation();
    last_element = NULL;
    bytes_encoded = 0;
    current_token = tokens;
    if (!current_token)
        invoke_error("empty token list int translate tokens\n", NULL, NULL); //message?
    while (current_token)
    {
        current_token_cast = (t_token *)current_token->stuff;
        if (current_token_cast->type == command_name)
            string_translation_mode = champ_name_string;
        else if (current_token_cast->type == command_comment)
            string_translation_mode = champ_comment_string;
        else if (current_token_cast->type == string && string_translation_mode == champ_name_string)
        {
            translation->champ_name = translate_champ_name(current_token, transcription_parameters, &bytes_encoded);
        }
        else if (current_token_cast->type == string && string_translation_mode == champ_comment_string)
        {
            translation->champ_comment = translate_champ_comment(current_token, transcription_parameters, &bytes_encoded);
        }
        else if (current_token_cast->type == operation)
        {
            current_token_translation = encode_operation(current_token_cast, &bytes_encoded);
            translation->exec_code = concatenate_lists(translation->exec_code, current_token_translation, last_element);
            last_element = current_token_translation;
            if (op_tab[get_operation_name(current_token_cast)].arg_code_flag)
            {
                current_token_translation = encode_type(current_token, &bytes_encoded);
                translation->exec_code = concatenate_lists(translation->exec_code, current_token_translation, last_element);
                last_element = current_token_translation;
            }
        }
        else if (current_token_cast->type == argument)
        {
            current_token_translation = encode_argument(current_token, tokens, labels, &bytes_encoded);
            translation->exec_code = concatenate_lists(translation->exec_code, current_token_translation, last_element);
            last_element = current_token_translation;
        }
        current_token = current_token->next;
    }
    return (concatenate_translation(translation));
}