/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallokoll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 12:32:14 by lcaesar           #+#    #+#             */
/*   Updated: 2020/06/23 12:55:14 by lcaesar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned int	why_length(const char *string)
{
	unsigned int n;

	n = 0;
	while (string[n] != '\0')
		n ++;
	return (n);
}

void			*mallokill(size_t size)
{
	void				*result;
	static const char	*message = "Malloc failed; Exiting;\n";

	result = malloc(size);
	if (!result)
	{
		write(STDERR_FILENO, message, why_length(message));
		exit(1);
	}
	return (result);
}