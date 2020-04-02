#include "generic_list.h"
#include "tokens.h"
#include "operation_table.h"
#include "function_prototypes.h"

t_generic_list *translate_tokens(t_generic_list *tokens,
t_generic_list *labels, t_transcription_parameters *transcription_parameters)
{
    t_generic_list *translation;
    t_generic_list *current_token;
    t_generic_list *current_token_translation;
    t_generic_list *last_element;
    t_token *current_token_cast;
    int bytes_encoded;
    
    int string_translation_mode; //1 for name, 2 for comment? THIS APPROACH IS FUCKED UP;

    char *debug_string;

    string_translation_mode = 1;
    translation = NULL;
    last_element = NULL;
    bytes_encoded = 0;
    current_token = tokens;
    if (!current_token)
        invoke_error("empty token list"); //message?
    while (current_token)
    {
        current_token_cast = (t_token *)current_token->stuff;
        if (current_token_cast->type == command_name)
        {
            string_translation_mode = 1;
        }
        else if (current_token_cast->type == command_comment)
        {
            string_translation_mode = 2;
        }
        else if (current_token_cast->type == string && string_translation_mode == 1) //make a separate function ffs;
        {
            current_token_translation = encode_string(current_token_cast, &bytes_encoded);
            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = get_last_element(current_token_translation);
            //
            // display_byte_strings(translation);
            //

            //REMAINING BYTES
            if (bytes_encoded > PROG_NAME_LENGTH)
                invoke_error("champ name is too long;");
            current_token_translation = get_null_padding(PROG_NAME_LENGTH - transcription_parameters->name_size);
            translation = concatenate_lists(translation, current_token_translation, last_element);
            //
            // display_byte_strings(translation);
            //
            last_element = get_last_element(current_token_translation);

            //PADDING
            current_token_translation = get_null_padding(PADDING_SIZE);
            //
            // display_byte_strings(current_token_translation);
            //
            translation = concatenate_lists(translation, current_token_translation, last_element);
            //
            // display_byte_strings(translation);
            //
            last_element = get_last_element(current_token_translation);

            //EXEC CODE SIZE
            current_token_translation = new_generic_list(decimal_to_hex(transcription_parameters->exec_code_size, 4));
            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = get_last_element(current_token_translation);
            //
            // display_byte_strings(translation);
            //
        }
        else if (current_token_cast->type == string && string_translation_mode == 2)
        {
            current_token_translation = encode_string(current_token_cast, &bytes_encoded);
            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = get_last_element(current_token_translation);
            //REMAINING BYTES
            if (bytes_encoded > COMMENT_LENGTH)
                invoke_error("champ comment is too long;");
            current_token_translation = get_null_padding(COMMENT_LENGTH - transcription_parameters->comment_size);
            translation = concatenate_lists(translation, current_token_translation, last_element);
            //
            // display_byte_strings(translation);
            //
            last_element = get_last_element(current_token_translation);

            //PADDING
            current_token_translation = get_null_padding(PADDING_SIZE);
            //
            // display_byte_strings(current_token_translation);
            //
            translation = concatenate_lists(translation, current_token_translation, last_element);
            //
            // display_byte_strings(translation);
            //
            last_element = get_last_element(current_token_translation);
        }
        else if (current_token_cast->type == operation)
        {
            current_token_translation = encode_operation(current_token_cast, &bytes_encoded);

            debug_string = current_token_translation->stuff;

            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = current_token_translation;
            if (op_tab[get_operation_name(current_token_cast)].arg_code_flag)
            {
                current_token_translation = encode_type(current_token, &bytes_encoded);

                debug_string = current_token_translation->stuff;

                translation = concatenate_lists(translation, current_token_translation, last_element);
                last_element = current_token_translation;
            }
        }
        else if (current_token_cast->type == argument)
        {
            current_token_translation = encode_argument(current_token, tokens, labels, &bytes_encoded);

            debug_string = current_token_translation->stuff;

            translation = concatenate_lists(translation, current_token_translation, last_element);
            last_element = current_token_translation;
        }
        current_token = current_token->next;
    }
    return (translation);
}