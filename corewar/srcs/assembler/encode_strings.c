/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encode_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:43:42 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:44:43 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

int				check_ascii_string(const char *string)
{
	unsigned int n;

	n = 0;
	while (string[n] != '\0')
	{
		if (!ft_isascii(string[n]))
			return (0);
		n = n + 1;
	}
	return (1);
}

t_generic_list	*get_null_padding(int number_of_bytes)
{
	int				n;
	t_generic_list	*encoding;

	n = 0;
	encoding = NULL;
	while (n < number_of_bytes)
	{
		encoding = add_to_list(encoding, ft_strdup("00"));
		n = n + 1;
	}
	return (encoding);
}

t_generic_list	*encode_string(t_token *token)
{
	int				n;
	t_generic_list	*encoding;
	char			*current_byte;
	void			*pointer;

	n = 0;
	encoding = NULL;
	while (token->string[n] != '\0')
	{
		if (token->string[n] != '"')
		{
			current_byte =
			ft_itoa_base_local(token->string[n], NUMBER_SYSTEM_BASE);
			if (ft_strlen(current_byte) < 2)
			{
				pointer = current_byte;
				current_byte = concat("0", current_byte);
				free(pointer);
			}
			encoding = add_to_list(encoding, current_byte);
		}
		n = n + 1;
	}
	return (encoding);
}
