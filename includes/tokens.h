#ifndef TOKENS_H
# define TOKENS_H

# include "op.h"
# include "generic_list.h"

typedef struct s_line_token t_line_token;
typedef struct s_token t_token;
typedef struct s_transcription_parameters t_transcription_parameters;
typedef struct s_container t_container;
typedef struct s_translation t_translation;
typedef struct s_buffer t_buffer;
typedef short t_token_list_status;

enum e_token_type
{
	null,
	unknown,
	command_name,
	command_comment,
	champ_name,
	champ_comment,
	label,
	operation,
	argument,
	comma,
	new_line
};

enum e_argument_type
{
	not_applicable,
	registry = T_REG,
	direct = T_DIR,
	indirect = T_IND
};

enum e_status_code
{
	name_code = 1,
	comment_code = 0,
};

enum e_buffer_status
{
	green,
	red,
};

enum e_string_writing_mode
{
	regular,
	inside_string,
};

struct s_line_token
{
	int index;
	char *label;
	char *operation;
	char *arguments;
};

struct s_token
{
	char *string;
	enum e_token_type type;
	enum e_argument_type argument_type;
	int size;
	int distance;
};

struct s_transcription_parameters
{
	int name_size;
	int comment_size;
	int exec_code_size;
};

struct s_translation
{
	t_generic_list *champ_name;
	t_generic_list *champ_comment;
	t_generic_list *exec_code;
};

struct s_container
{
	int file_descriptor;
	int size_of_tokens;
	const char *file_name;
	char *new_file_name;
	t_generic_list *tokens;
	t_generic_list *current;
	t_generic_list *labels;
	t_generic_list *translated_tokens;
	t_transcription_parameters *parameters;
	t_translation *translation;
	t_token_list_status status;
};

struct s_buffer
{
	char *content;
	unsigned int current_content_size;
	unsigned int max_content_size;
	enum e_string_writing_mode mode;
	enum e_buffer_status status;
};

#endif