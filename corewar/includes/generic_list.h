/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar <lcaesar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 17:33:37 by lcaesar           #+#    #+#             */
/*   Updated: 2020/06/27 19:31:42 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERIC_LIST_H
# define GENERIC_LIST_H

# include <stdlib.h>

typedef struct s_generic_list	t_generic_list;

struct			s_generic_list
{
	void			*stuff;
	t_generic_list	*next;
};

t_generic_list	*new_generic_list(void *stuff);
t_generic_list	*add_to_list(t_generic_list *list, void *stuff);
int				count_generic_list_objects(t_generic_list *generic_list);
int				is_on_the_list(t_generic_list *generic_list, void *stuff);
void			destroy_generic_list(t_generic_list **generic_list,
				void (*destructor)(void *));

t_generic_list	*get_last_element(t_generic_list *list);
t_generic_list	*concatenate_lists(t_generic_list *base_list,
t_generic_list *augmenting_list, t_generic_list *last_element);

#endif
