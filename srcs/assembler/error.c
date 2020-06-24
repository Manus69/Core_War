/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 23:36:42 by lcaesar           #+#    #+#             */
/*   Updated: 2020/06/23 23:37:55 by lcaesar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

//dont forget to change the output file descriptor
int invoke_error(const char *error_message, t_token *token,
const char *current_string, t_container *container)
{
	extern const char   *g_file_name;

	ft_printf("file name: %s\n", g_file_name);
	ft_printf("%s", error_message);
	if (token)
		display_token(token);
	if (current_string)
		ft_printf("%s", current_string);
	if (container)
		destroy_container(&container);
	exit(1);
	return (1);
}