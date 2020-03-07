/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_name_comment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 13:34:37 by gemerald          #+#    #+#             */
/*   Updated: 2020/03/07 13:36:12 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		put_labels(t_dsm *src_code, char *string, char *to_enlarge)
{
	int		i;
	size_t	len;

	i = -1;
	len = ft_strlen(to_enlarge);
	while (src_code->output_position < OUTPUT_LEN && string[++i])
	{
		src_code->output[src_code->output_position] = string[i];
		src_code->output_position++;
	}
	while (src_code->output_position < OUTPUT_LEN &&
			src_code->output_position < len)
	{
		src_code->output[src_code->output_position] = ' ';
		src_code->output_position++;
	}
	return (SUCCESS);
}

int		put_comment(t_dsm *src_code)
{
	int i;

	i = -1;
	put_labels(src_code, COMMENT_CMD_STRING, NAME_CMD_STRING);
	src_code->output[src_code->output_position++] = '\t';
	src_code->output[src_code->output_position++] = '"';
	while (src_code->output_position < OUTPUT_LEN &&
			src_code->fill_file.comment[++i])
	{
		src_code->output[src_code->output_position] =\
			(char)src_code->fill_file.comment[i];
		src_code->output_position++;
	}
	src_code->output[src_code->output_position++] = '"';
	src_code->output[src_code->output_position++] = '\n';
	src_code->output[src_code->output_position++] = '\n';
	return (SUCCESS);
}

int		put_name(t_dsm *src_code)
{
	int i;

	i = -1;
	put_labels(src_code, NAME_CMD_STRING, COMMENT_CMD_STRING);
	src_code->output[src_code->output_position++] = '\t';
	src_code->output[src_code->output_position++] = '"';
	while (src_code->output_position < OUTPUT_LEN &&
			src_code->fill_file.name[++i])
	{
		src_code->output[src_code->output_position] =\
			(char)src_code->fill_file.name[i];
		src_code->output_position++;
	}
	src_code->output[src_code->output_position++] = '"';
	src_code->output[src_code->output_position++] = '\n';
	return (SUCCESS);
}

int		put_name_comment(t_dsm *src_code)
{
	if ((ft_strlen(NAME_CMD_STRING) + ft_strlen(COMMENT_CMD_STRING)) >\
			(OUTPUT_LEN / 4))
		return (FAIL);
	if (!put_name(src_code) || !put_comment(src_code))
		return (FAIL);
	src_code->output[src_code->output_position] = '\0';
	return (SUCCESS);
}
