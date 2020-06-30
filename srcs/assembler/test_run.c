/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcaesar  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 13:03:33 by lcaesar           #+#    #+#             */
/*   Updated: 2020/06/23 13:03:33 by lcaesar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char        *get_new_filename(t_container *container, t_flag *has_flag)
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

void        translate_and_write_to_file(t_container *container, t_flag *has_flag)
{
    int             file;
    t_generic_list  *prefix_item;
    char            *new_file_name;

    prefix_item = new_generic_list(ft_strdup("00ea83f3"));
    prefix_item = concatenate_lists(prefix_item,
    translate_tokens(container, has_flag), NULL);
    if (has_flag->visible) //what flag is that? 
        display_byte_strings(prefix_item);
    if (has_flag->flag_a)
        display_all_tokens(container->tokens, STDOUT_FILENO);
    new_file_name = get_new_filename(container, has_flag);
    if (container->error_status)
        invoke_error("Compilation terminated;\n", NULL, NULL, container);
    file = open(new_file_name, O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (file < 0)
        invoke_error("Open / create failure", NULL, NULL, container);
    tokens_to_bytes(prefix_item, file);
    ft_printf("Writing output program to %s\n", new_file_name); //make a string constant message?
    close(file);
    if (!has_flag->change_name)
    	free(new_file_name);
    destroy_generic_list(&prefix_item, free);
}

void        here_we_go(char *file_name, t_flag *has_flag)
{
    t_container *container;

    container = new_container(file_name);
    // g_file_name = file_name;
    read_file(container);
    close(container->file_descriptor);
    classify_all_tokens(container);
    //
    // display_all_tokens(container->tokens, 2);
    // exit(1);
    //
    measure_token_size(container->tokens);
    set_global_distance(container);
    get_transcription_parameters(container);
    translate_and_write_to_file(container, has_flag);
    destroy_container(&container);
}
