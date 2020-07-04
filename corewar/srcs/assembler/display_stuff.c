/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:13:43 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:15:49 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

void		display_all_tokens(t_generic_list *tokens, int fd)
{
	t_generic_list *current;

	current = tokens;
	while (current != NULL)
	{
		display_token((t_token *)current->stuff, fd);
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

	index = 0;
	length = ft_strlen(string);
	if (length == 0 || (length % 2) != 0)
		invoke_error("in string to bytes: string is broken:", NULL,
				string, NULL);
	while (index < length)
	{
		current_byte = ft_strsub(string, index, 2);
		ft_putchar_fd(ft_atoi_base(current_byte, NUMBER_SYSTEM_BASE),
				file_descriptor);
		free(current_byte);
		index = index + 2;
	}
}

void		tokens_to_bytes(t_generic_list *tokens, int file_descriptor)
{
	t_generic_list *current_token;

	current_token = tokens;
	while (current_token)
	{
		string_to_bytes(current_token->stuff, file_descriptor);
		current_token = current_token->next;
	}
}
