#include "generic_list.h"
#include "tokens.h"
#include "ft_printf.h"
#include "libft.h"

void	*mallokill(size_t size);

int is_a_member(char *set, char c);

void display_token(t_token *token);
void display_all_tokens(t_generic_list *tokens);
void display_classification_error_message(t_token *token, int verbose);

int     is_quotation_mark(t_token *current_token, t_token *previous_token);
int     is_label(t_token *current_token, t_token *previous_token);
int     is_hashtag(t_token *current_token, t_token *previous_token);
int     is_operation(t_token *current_token, t_token *previous_token);