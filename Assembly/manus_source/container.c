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
    // check_terminator(container->file_descriptor);
    container->size_of_tokens = -1;
    container->new_file_name = NULL;
    container->tokens = NULL;
    container->labels = NULL;
    container->parameters = new_parameters();
    container->translated_tokens = NULL;
    container->translation = new_translation();

    return (container);
}