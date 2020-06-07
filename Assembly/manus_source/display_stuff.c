#include "function_prototypes.h"
#include "ft_printf.h"

void		display_all_tokens(t_generic_list *tokens)
{
	t_generic_list *current;

	current = tokens;
	while (current != NULL)
	{
		display_token((t_token *)current->stuff);
		current = current->next;
	}
}

void		display_byte_strings(t_generic_list *tokens)
{
	t_generic_list *current;

	current = tokens;
	while (current)
	{
		ft_printf("%s", current->stuff);
		current = current->next;
	}
	ft_printf("\n");
}

void		string_to_bytes(char *string, int file_descriptor)
{
	int				index;
	int				length;
	char			*current_byte;
	unsigned char	byte_value;

	index = 0;
	length = ft_strlen(string);

	if (length == 0 || (length % 2) != 0)
		invoke_error("in string to bytes: string is broken:", NULL, string, NULL); //this is a debug message, it will go away

	while (index < length)
	{
		current_byte = ft_strsub(string, index, 2);
		ft_dprintf(file_descriptor, "%c", ft_atoi_base(current_byte, NUMBER_SYSTEM_BASE));
		free(current_byte);
		index = index + 2;
	}
}

void		tokens_to_bytes(t_generic_list *tokens, int file_descriptor)
{
	t_generic_list *current_token;

	current_token = tokens;
	while(current_token)
	{
		string_to_bytes(current_token->stuff, file_descriptor);
		current_token = current_token->next;
	}
}

