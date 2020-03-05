#ifndef FUNCTION_PROTOTYPES_H
# define FUNCTION_PROTOTYPES_H
# include "generic_list.h"
# include "tokens.h"
# include "ft_printf.h"
# include "libft.h"

void	*mallokill(size_t size);

int is_a_member(char *set, char c);

void display_token(t_token *token);
void display_all_tokens(t_generic_list *tokens);
void display_classification_error_message(t_token *token, int verbose);

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

#endif