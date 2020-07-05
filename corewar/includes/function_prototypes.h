/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_prototypes.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 18:04:28 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/03 18:26:35 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_PROTOTYPES_H
# define FUNCTION_PROTOTYPES_H
# include "generic_list.h"
# include "tokens.h"
# include "printf.h"
# include "asm.h"
# include "libft.h"

/*
** support
*/

void			*mallokill(size_t size);
int				generic_token_string_check(char *string,
				char character, int start);
int				check_substring_characters(char *string,
				int start_index, int end_index, char *set);
int				check_symbol(char *string, char symbol);
int				is_string_in_array(char *string, const char **string_array);
int				is_a_member(const char *set, char c);
int				is_in_string(const char *string, char c);
char			*get_binary_complement(char *binary_number,
				int number_of_bytes);
void			carry_propagate(char *number, int index, int bytes_left);
int				binary_to_decimal(char *binary_number);
char			*decimal_to_hex(int n, int number_of_bytes);
char			*concat(char *lhs, char *rhs);
int				get_next_index(const char *string,
				int start, const char *char_set);
char			skip_to_char(int file, char c);
char			get_char(int file);
char			*decimal_to_hex_mk2(int n, int number_of_bytes);
char			*ft_itoa_base_local(unsigned int n, unsigned int base);
long			why_atol(const char *number_string);

/*
** display
*/

void			display_token(t_token *token, int fd);
void			display_all_tokens(t_generic_list *tokens, int fd);
void			display_byte_strings(t_generic_list *tokens);
void			string_to_bytes(char *string, int file_descriptor);
void			tokens_to_bytes(t_generic_list *tokens, int file_descriptor);
int				invoke_error(const char *error_message, t_token *token,
				const char *current_string, t_container *container);
void			display_character_error(int error_code,
				t_buffer *buffer, t_container *container);

/*
** classification
*/

int				is_quotation_mark(char *string);
int				is_label(char *string);
int				is_comment_character(char *string);
int				is_operation(char *string);
int				is_new_line(char *string);
int				is_command(char *string);
int				is_command_name(char *string);
int				is_command_comment(char *string);
int				is_argument_separator(char *string);
int				is_registry(char *string);
int				is_direct(char *string);
int				is_indirect(char *string);
int				is_string(char *string);
int				check_argument_token(t_token *token);
void			classify_after_null(t_token *current_token);
void			classify_after_new_line(t_token *current_token);
void			classify_after_label(t_token *current_token);
void			classify_after_argument(t_token *current_token);
void			classify_after_operation(t_token *current_token);

/*
** encoding
*/

t_generic_list	*encode_string(t_token *token);
t_generic_list	*get_null_padding(int number_of_bytes);
t_generic_list	*encode_operation(t_token *token);
char			*get_registry_encoding(t_token *token, t_container *container);
t_generic_list	*encode_argument(t_generic_list *token,
t_generic_list	*tokens, t_container *container);
t_generic_list	*encode_type(t_generic_list *token);
t_op_name		get_operation_name(t_token *token);
int				get_distance_to_the_label(t_generic_list *token,
				char *label_name, t_generic_list *tokens,
				t_container *container);
void			set_global_distance(t_container *container);
int				get_distance_to_the_previous_operation(t_token *token,
				t_generic_list *token_list);
t_generic_list	*get_next_typed_token(t_generic_list *tokens,
				enum e_token_type type);

void			get_transcription_parameters(t_container *container);

/*
** translation
*/

t_translation	*new_translation(void);
void			destroy_translation(t_translation **translation);
t_generic_list	*translate_tokens(t_container *container, t_flag *has_flag);
t_generic_list	*translate_champ_name(t_generic_list *current_token,
				t_container *container);
t_generic_list	*translate_champ_comment(t_generic_list *current_token,
				t_container *container);
t_generic_list	*concatenate_translation(const t_translation *translation);
void			compare_arg_counts(t_generic_list *token,
				t_container *container);
int				get_operation_code(t_token *token);
void			compare_arg_type(t_token *prev,
				t_token *cur, t_container *cont, t_flag *flag);

/*
** token
*/

t_token			*new_token(char *string, enum e_token_type type);
t_token			*copy_token(t_token *token);
void			destroy_token_dumb(void *token);
void			classify_token(t_token *current_token,
				t_token *previous_token);
void			classify_all_tokens(t_container *container);
void			here_we_go(char *str, t_flag *has_flag);
void			measure_token_size(t_generic_list *tokens);

/*
** container
*/

t_container		*new_container(const char *file_name);
void			destroy_container(t_container **container);

/*
** buffer
*/

t_buffer		*new_buffer(unsigned int size);
void			destroy_buffer(t_buffer **buffer);
int				add_to_buffer(t_buffer *buffer, char c);
void			append_buffer_to_tokens(t_container *container,
				t_buffer *buffer);

/*
** status
*/

void			set_status(t_container *container, t_token *token);

/*
** file
*/

void			read_file(t_container *container);
char			*pad_with_chars(char *string,
				unsigned int pad_size, char c, int side);
char			*join_and_free(char *lhs, char *rhs);
char			*replace_extension(const char *file_name,
				t_container *container);
char			*trim_file_name(const char *file_name,
				t_container *container);

#endif
