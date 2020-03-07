#ifndef FUNCTION_PROTOTYPES_H
# define FUNCTION_PROTOTYPES_H
# include "generic_list.h"
# include "tokens.h"
# include "ft_printf.h"
# include "libft.h"

void	*mallokill(size_t size);

int is_a_member(char *set, char c);
char *get_binary_complement(char *binary_number, int number_of_bytes);
void carry_propagate(char *number, int index, int bytes_left); //make it static later;
int binary_to_decimal(char *binary_number);
char *decimal_to_hex(int n, int number_of_bytes);

void display_token(t_token *token);
void display_all_tokens(t_generic_list *tokens);
void display_classification_error_message(t_token *token, int verbose);
void display_byte_strings(t_generic_list *tokens);

int     is_quotation_mark(char *string);
int     is_label(char *string);
int     is_comment_character(char *string);
int     is_operation(char *string);
int     is_new_line(char *string);
int     is_command(char *string);
int     is_argument_separator(char *string);

int     is_registry(char *string);
int     is_direct(char *string);
int     is_indirect(char *string);

int     check_argument_token(t_token *token);

t_generic_list *encode_string(t_token *token, int *bytes_encoded);
t_generic_list *get_null_padding(int number_of_bytes);
t_generic_list *encode_string_tokens(t_generic_list *tokens, int *bytes_encoded);
t_generic_list *encode_operation(t_token *token, int *bytes_encoded);

char *get_type_encoding(int number_of_arguments, ...);
t_generic_list *get_type_encoding_mk2(t_generic_list *token, int *bytes_encoded);

#endif