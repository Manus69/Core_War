/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 16:49:17 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 16:49:54 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	display_translation_errors(t_container *container)
{
	int		n;
	short	power;
	char	*message;

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
		n ++;
		power = power << 1;
	}
}

int		invoke_error(const char *error_message, t_token *token,
		const char *current_string, t_container *container)
{

	ft_putstr_fd("File name: ", STDERR_FILENO);
	ft_putstr_fd(container->file_name, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (container->error_status)
		display_translation_errors(container);
	if (error_message)
		ft_putstr_fd(error_message, STDERR_FILENO);
	if (token)
		display_token(token, STDERR_FILENO);
	if (current_string)
		ft_putstr_fd(current_string, STDERR_FILENO);
	if (container)
		destroy_container(&container);
	exit(1);
	return (1);
}
