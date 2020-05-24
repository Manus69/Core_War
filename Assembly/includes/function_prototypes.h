#ifndef FUNCTION_PROTOTYPES_H
# define FUNCTION_PROTOTYPES_H
# include "generic_list.h"
# include "tokens.h"
# include "ft_printf.h"
# include "libft.h"
# include <fcntl.h>
# include <sys/types.h>

void	*mallokill(size_t size);

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

//testing;
char *decimal_to_hex_mk2(int n, int number_of_bytes);
char *ft_itoa_base_local(unsigned int n, unsigned int base);
long why_atol(const char *number_string);
int check_number_string(const char *number_string);
//

char *replace_extension(const char *file_name);
char *trim_file_name(const char *file_name);

void display_token(t_token *token);
void display_all_tokens(t_generic_list *tokens);
void display_classification_error_message(t_token *token, int verbose);
void display_byte_strings(t_generic_list *tokens);

void string_to_bytes(char *string, int file_descriptor);
void tokens_to_bytes(t_generic_list *tokens, int file_descriptor);

void invoke_error(const char *error_message, t_token *current_token, const char *current_string);

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

//this is bad;
int     is_multistring_start(char *string);
int     is_multistring_end(char *string);
int     is_multistring(char *string);
//

void    set_token_size(t_token *token);
void    measure_token_size(t_generic_list *tokens);

int     check_argument_token(t_token *token);

t_generic_list *encode_string(t_token *token, int *bytes_encoded);
t_generic_list *get_null_padding(int number_of_bytes);
t_generic_list *encode_string_tokens(t_generic_list *tokens, int *bytes_encoded);
t_generic_list *encode_operation(t_token *token, int *bytes_encoded);

char *get_registry_encoding(t_token *token);
char *get_direct_number_encoding(t_token *token);
t_generic_list *encode_argument(t_generic_list *token,
t_generic_list *tokens, t_generic_list *labels, int *bytes_encoded);

char *grab_n_bytes_from_address(t_generic_list *tokens, int address, int number_of_bytes);

char *get_type_encoding(int number_of_arguments, ...);
t_generic_list *encode_type(t_generic_list *token, int *bytes_encoded);
enum e_operation_name get_operation_name(t_token *token);

int get_distance_to_the_label(t_generic_list *token, char *label_name,
t_generic_list *tokens, t_generic_list *labels);
void set_global_distance(t_container *container);
int get_distance_to_the_previous_operation(t_token *token, t_generic_list *token_list);

t_generic_list *get_next_typed_token(t_generic_list *tokens, enum e_token_type type);
void get_transcription_parameters(t_container *container);

t_generic_list *translate_tokens(t_generic_list *tokens,
t_generic_list *labels, t_transcription_parameters *transcription_parameters);

t_token *new_token(char *string, enum e_token_type type);
t_token *get_next_token(int *n, char *line);
t_generic_list *line_to_tokens(char *line);

void classify_token(t_token *current_token, t_token *previous_token, int verbose);
void classify_all_tokens(t_generic_list *tokens, t_generic_list **labels, int verbose);

void here_we_go(char *str);

//container
// struct s_transcription_parameters *new_parameters(void);
t_container *new_container(const char *file_name);

#endif