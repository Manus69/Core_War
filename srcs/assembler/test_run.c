/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 17:37:20 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/03 17:42:18 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "constants.h"

char		*get_new_filename(t_container *container, t_flag *has_flag)
{
	char *new_file_name;
	void *pointer;

	if (has_flag->change_name)
		new_file_name = has_flag->new_file_name;
	else
	{
		new_file_name = trim_file_name(container->file_name, container);
		pointer = new_file_name;
		new_file_name = replace_extension(new_file_name, container);
		free(pointer);
	}
	return (new_file_name);
}

void		clean_up(t_generic_list *prefix_item, int file,
			t_flag *has_flag, char *new_file_name)
{
	if (file >= 0)
		close(file);
	if (!has_flag->change_name)
		free(new_file_name);
	destroy_generic_list(&prefix_item, free);
}

void		process_flags(t_container *container,
			t_flag *has_flag, t_generic_list *prefix_item)
{
	if (has_flag->visible)
		display_byte_strings(prefix_item);
	if (has_flag->flag_a)
		display_all_tokens(container->tokens, STDOUT_FILENO);
}

void		translate_and_write_to_file(t_container *container,
			t_flag *has_flag)
{
	int				file;
	t_generic_list	*prefix_item;
	char			*new_file_name;

	prefix_item = new_generic_list(ft_strdup("00ea83f3"));
	prefix_item = concatenate_lists(prefix_item,
	translate_tokens(container, has_flag), NULL);
	new_file_name = get_new_filename(container, has_flag);
	if (container->error_status)
	{
		clean_up(prefix_item, -1, has_flag, new_file_name);
		invoke_error(COMPILATION_TERMINATED, NULL, NULL, container);
	}
	process_flags(container, has_flag, prefix_item);
	file = open(new_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (file < 0)
	{
		clean_up(prefix_item, file, has_flag, new_file_name);
		invoke_error(OPEN_CREATE_FAILURE, NULL, NULL, container);
	}
	tokens_to_bytes(prefix_item, file);
	ft_printf("Writing output program to %s\n", new_file_name);
	clean_up(prefix_item, file, has_flag, new_file_name);
}

void		here_we_go(char *file_name, t_flag *has_flag)
{
	t_container *container;

	container = new_container(file_name);
	read_file(container);
	close(container->file_descriptor);
	classify_all_tokens(container);
	measure_token_size(container->tokens);
	set_global_distance(container);
	get_transcription_parameters(container);
	translate_and_write_to_file(container, has_flag);
	destroy_container(&container);
}
