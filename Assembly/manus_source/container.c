#include "tokens.h"
#include "function_prototypes.h"

struct s_transcription_parameters *new_parameters(void)
{
    struct s_transcription_parameters *parameters;

    parameters = mallokill(sizeof(struct s_transcription_parameters));
    parameters->name_size = -1;
    parameters->comment_size = -1;
    parameters->exec_code_size = -1;

    return (parameters);
}

t_container *new_container(const char *file_name)
{
    t_container *container;

    container = mallokill(sizeof(t_container));

    container->file_name = file_name;
    container->file_descriptor = open(file_name, O_RDONLY);
    if (container->file_descriptor < 0)
        invoke_error(FILE_ERROR_MESSAGE, NULL, NULL);
    container->size_of_tokens = -1;
    container->new_file_name = NULL;
    container->tokens = NULL;
    container->labels = NULL;
    container->parameters = new_parameters();
    container->translated_tokens = NULL;
    container->translation = new_translation();
    container->status = 0;

    return (container);
}

void destroy_container(t_container **container)
{
    destroy_generic_list(&(*container)->tokens, destroy_token_dumb);
    // destroy_generic_list(&(*container)->labels, NULL);
    free((*container)->parameters);
    destroy_translation(&(*container)->translation);
    free(*container);
    *container = NULL;
}