/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binary_read.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:30:45 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:32:09 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_char			*ft_create_elem(char c)
{
	t_char *tmp;

	if (!(tmp = (t_char *)malloc(sizeof(t_char))))
		return (NULL);
	tmp->next = NULL;
	tmp->c = c;
	return (tmp);
}

static void				ft_list_del(t_char **begin_list)
{
	t_char *link;
	t_char *f_link;

	link = *begin_list;
	while (link != NULL)
	{
		f_link = link->next;
		free(link);
		link = f_link;
	}
}

static void				ft_push_back(t_char **begin_list, unsigned char c)
{
	t_char *list;

	list = *begin_list;
	if (list != NULL)
	{
		while (list->next)
			list = list->next;
		if (!(list->next = ft_create_elem(c)))
			ft_list_del(&list);
	}
	else
	{
		if (!(*begin_list = ft_create_elem(c)))
			ft_list_del(begin_list);
	}
}

static unsigned char	*ft_concat(t_char **begin_list, int list_len)
{
	int					index;
	unsigned char		*str;
	t_char				*list;

	list = *begin_list;
	index = 0;
	if (!(str = (unsigned char *)malloc(sizeof(char) * list_len)))
		return (NULL);
	while (index < list_len)
	{
		str[index] = list->c;
		list = list->next;
		index++;
	}
	return (str);
}

unsigned char			*ft_binary_read(int fd, size_t *len)
{
	unsigned char		buf;
	unsigned char		*str;
	int					list_len;
	t_char				*list;

	list = NULL;
	list_len = 0;
	str = NULL;
	if ((read(fd, &buf, 0)) < 0)
		return (NULL);
	while ((read(fd, &buf, 1)))
	{
		ft_push_back(&list, buf);
		list_len++;
	}
	if (list)
	{
		str = ft_concat(&list, list_len);
		*len = list_len;
		ft_list_del(&list);
	}
	return (str);
}
