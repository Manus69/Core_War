/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:49:17 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/03 17:31:01 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"
#include "tables.h"

void	display_translation_errors(t_container *container)
{
	int			n;
	short		power;
	const char	*message;

	n = 0;
	power = 1;
	while (power < E_MAX)
	{
		if (container->error_status & power)
		{
			message = g_error_messages[n];
			if (!message)
			{
				ft_putstr_fd(UNEXPECTED_ERROR, STDERR_FILENO);
				break ;
			}
			ft_putstr_fd(g_error_messages[n], STDERR_FILENO);
		}
		n++;
		power = power << 1;
	}
}

void	display_character_error(int error_code,
		t_buffer *buffer, t_container *container)
{
	destroy_buffer(&buffer);
	ft_putstr_fd(g_character_errors[error_code], STDERR_FILENO);
	invoke_error(COMPILATION_TERMINATED, NULL, NULL, container);
}

int		invoke_error(const char *error_message, t_token *token,
		const char *current_string, t_container *container)
{
	ft_putstr_fd("File name: ", STDERR_FILENO);
	if (container)
		ft_putstr_fd(container->file_name, STDERR_FILENO);
	if (current_string)
		ft_putstr_fd(current_string, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (container && container->error_status)
		display_translation_errors(container);
	if (error_message)
		ft_putstr_fd(error_message, STDERR_FILENO);
	if (token)
		display_token(token, STDERR_FILENO);
	if (container)
		destroy_container(&container);
	exit(1);
	return (1);
}
