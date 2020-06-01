#ifndef FUNCTION_PROTOTYPES_H
# define FUNCTION_PROTOTYPES_H
# include "generic_list.h"
# include "tokens.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>

void	*mallokill(size_t size);

//check
int     generic_token_string_check(char *string, char character, int start);
int     check_substring_characters(char *string, int start_index, int end_index, char *set);
int     check_symbol(char *string, char symbol);


int     is_string_in_array(char *string, char **string_array);
int is_a_member(const char *set, char c);
int is_in_string(const char *string, char c);
char *get_binary_complement(char *binary_number, int number_of_bytes);
void carry_propagate(char *number, int index, int bytes_left); //make it static later;
int binary_to_decimal(char *binary_number);
char *decimal_to_hex(int n, int number_of_bytes);
char *concat(char *lhs, char *rhs);

int get_next_index(const char *string, int start, const char *char_set);
char *get_next_substring(const char *string, int *start,
const char *start_char_set, const char *end_char_set);
char skip_to_char(int file, char c);
char get_char(int file);

//testing;
char *decimal_to_hex_mk2(int n, int number_of_bytes);
char *ft_itoa_base_local(unsigned int n, unsigned int base);
long why_atol(const char *number_string);
int check_number_string(const char *number_string);
//

char *replace_extension(const char *file_name, t_container *container);
char *trim_file_name(const char *file_name, t_container *container);

void display_token(t_token *token);
void display_all_tokens(t_generic_list *tokens);
void display_classification_error_message(t_token *token, int verbose);
void display_byte_strings(t_generic_list *tokens);

void string_to_bytes(char *string, int file_descriptor);
void tokens_to_bytes(t_generic_list *tokens, int file_descriptor);

int invoke_error(const char *error_message, t_token *token,
const char *current_string, t_container *t_container);
void invoke_destruction(const char *error_message, t_token *token,
const char *current_string, t_container *container);

int     is_quotation_mark(char *string);
int     is_label(char *string);
int     is_comment_character(char *string);
int     is_operation(char *string);
int     is_new_line(char *string);
int     is_command(char *string);

int     is_command_name(char *string);
int     is_command_comment(char *string);

int     is_argument_separator(char *string);

int     is_registry(char *string);
int     is_direct(char *string);
int     is_indirect(char *string);

int     is_string(char *string);

void    set_token_size(t_token *token);
void    measure_token_size(t_generic_list *tokens);

int     check_argument_token(t_token *token);

t_generic_list *encode_string(t_token *token);
t_generic_list *get_null_padding(int number_of_bytes);
t_generic_list *encode_string_tokens(t_generic_list *tokens);
t_generic_list *encode_operation(t_token *token);

char *get_registry_encoding(t_token *token, t_container *container);
char *get_direct_number_encoding(t_token *token);
t_generic_list *encode_argument(t_generic_list *token,
t_generic_list *tokens, t_container *container);

char *get_type_encoding(int number_of_arguments, ...);
t_generic_list *encode_type(t_generic_list *token);
enum e_operation_name get_operation_name(t_token *token);

int get_distance_to_the_label(t_generic_list *token, char *label_name,
t_generic_list *tokens, t_container *container);
void set_global_distance(t_container *container);
int get_distance_to_the_previous_operation(t_token *token, t_generic_list *token_list);

t_generic_list *get_next_typed_token(t_generic_list *tokens, enum e_token_type type);
void get_transcription_parameters(t_container *container);

//translation
struct s_translation *new_translation(void);
void destroy_translation(t_translation **translation);
t_generic_list *translate_tokens(t_container *container);

t_generic_list *translate_champ_name(t_generic_list *current_token,
t_container *container);
t_generic_list *translate_champ_comment(t_generic_list *current_token,
t_container *container);
t_generic_list *concatenate_translation(const struct s_translation *translation);

int get_arg_count(t_generic_list *token);
void compare_arg_counts(t_generic_list *token, t_container *container);
int get_operation_code(t_token *token);
void compare_arg_type(t_token *previous_operation, t_token *current_token, t_container *container);

//

t_token *new_token(char *string, enum e_token_type type);
t_token *copy_token(t_token *token);
void destroy_token(t_token **token_pointer);
void destroy_token_mk2(void *pp_token);
void destroy_token_dumb(void *token);
// t_token *get_next_token(int *n, char *line);
// t_generic_list *line_to_tokens(char *line);

void classify_token(t_token *current_token, t_token *previous_token);
void classify_all_tokens(t_container *container);
void preprocess_all_tokens(t_generic_list *tokens);

void here_we_go(char *str);

//container
t_container *new_container(const char *file_name);
void destroy_container(t_container **container);

//buffer
t_buffer *new_buffer(unsigned int size);
void destroy_buffer(t_buffer **buffer);
int add_to_buffer(t_buffer *buffer, char c);
void append_buffer_to_tokens(t_container *container, t_buffer *buffer);

//status
void set_status(t_container *container, t_token *token);

//read file
void read_file(t_container *container);

char *pad_with_chars(char *string, unsigned int pad_size, char c, int side);

char *join_and_free(char *lhs, char *rhs);

#endif