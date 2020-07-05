/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 15:45:51 by selly             #+#    #+#             */
/*   Updated: 2019/05/06 17:13:22 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*lsnext;

	while (*alst)
	{
		lsnext = (*alst)->next;
		del((*alst)->content, (*alst)->content_size);
		free(*alst);
		*alst = lsnext;
	}
	*alst = NULL;
}
