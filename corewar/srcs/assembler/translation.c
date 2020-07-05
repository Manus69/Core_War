/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 18:42:35 by gemerald          #+#    #+#             */
/*   Updated: 2020/06/27 18:45:44 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

struct s_translation	*new_translation(void)
{
	struct s_translation *translation;

	translation = mallokill(sizeof(struct s_translation));
	translation->champ_name = NULL;
	translation->champ_comment = NULL;
	translation->exec_code = NULL;
	return (translation);
}

void					destroy_translation(t_translation **translation)
{
	destroy_generic_list(&(*translation)->champ_name, NULL);
	destroy_generic_list(&(*translation)->champ_comment, NULL);
	destroy_generic_list(&(*translation)->exec_code, NULL);
	free(*translation);
	*translation = NULL;
}

t_generic_list			*concatenate_translation(const struct s_translation\
		*translation)
{
	t_generic_list *resulting_list;
	t_generic_list *last_in_name;
	t_generic_list *last_in_comment;

	last_in_name = get_last_element(translation->champ_name);
	last_in_comment = get_last_element(translation->champ_comment);
	resulting_list = translation->champ_name;
	resulting_list = concatenate_lists(resulting_list,
			translation->champ_comment, last_in_name);
	resulting_list = concatenate_lists(resulting_list,
			translation->exec_code, last_in_comment);
	return (resulting_list);
}
