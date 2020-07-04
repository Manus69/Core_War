/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_list_part2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 17:16:46 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 17:17:19 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_generic_list	*get_last_element(t_generic_list *list)
{
	t_generic_list *current;

	if (!list)
		return (NULL);
	current = list;
	while (current->next)
		current = current->next;
	return (current);
}

t_generic_list	*concatenate_lists(t_generic_list *base_list,
		t_generic_list *augmenting_list, t_generic_list *last_element)
{
	if (!base_list)
		return (augmenting_list);
	if (!augmenting_list)
		return (base_list);
	if (!last_element)
		last_element = get_last_element(base_list);
	last_element->next = augmenting_list;
	return (base_list);
}
