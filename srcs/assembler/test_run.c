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

const char  *g_file_name;

void        translate_and_write_to_file(t_container *container, t_flag *has_flag)
{
    int file;
    t_generic_list *prefix_item;
    char *new_file_name;
    void *pointer;

    prefix_item = new_generic_list(ft_strdup("00ea83f3"));
    prefix_item = concatenate_lists(prefix_item, translate_tokens(container, has_flag), NULL);
    pointer = NULL;
    if (has_flag->visible)
    {
        display_byte_strings(prefix_item);
        // return ;
    }
    if (has_flag->flag_a)
	{
    	ft_putstr("Here is -a flag!\n");
	}
    if (has_flag->change_name)
    	new_file_name = has_flag->new_file_name;
    else
    {
		new_file_name = trim_file_name(g_file_name, container);
		pointer = new_file_name;
		new_file_name = replace_extension(new_file_name, container);
	}
    file = open(new_file_name, O_RDWR | O_CREAT, 0777);
    if (file < 0)
        invoke_error("open / create failure", NULL, NULL, container); // EMSG
    tokens_to_bytes(prefix_item, file); //change for a suitable file descriptor;
    ft_printf("Writing output program to %s\n", new_file_name); //make a string constant message?

    close(file);
    free(pointer);
    if (!has_flag->change_name)
    	free(new_file_name);
    destroy_generic_list(&prefix_item, free);
}

/*questionable*/
//tab at the end of file instead of \n? both asms work with \t right now; 
//there is a free(NULL) in encode args
//

//where are the files supposed to go if one runs the pogramme from a different directory?
//remove the file that might have been created after the error invocation;

//empty champ name?
//error messages

//disassmbler crashed on some input

//do i need to check the file size?
//set the right buffer size

//check included system headers
//non-ascii characters?
//malloc return value checks? use mallokill consistently?
//ft_memchr() memccpy() send off compiler warnings;

//add checks for add to buffer calls, since it cant call invoke_error anymore
//test number arguments in different byte ranges with different signs; make it systematic
//leaks on invalid input?
//scuffed filenames? short, empty? 

//dont give retards an inch


void        here_we_go(char *file_name, t_flag *has_flag)
{
    t_container *container;

    //testing area

    container = new_container(file_name);
    //
    g_file_name = file_name; //used in invoke error calls
    //

    read_file(container);
    close(container->file_descriptor);
    //
    // display_all_tokens(container->tokens);
    // exit(1);
    //
    classify_all_tokens(container);
    //
    // display_all_tokens(container->tokens);
    // exit(1);
    //
    measure_token_size(container->tokens);
    set_global_distance(container);
    //
    // display_all_tokens(container->tokens);
    // exit(1);
    //
    get_transcription_parameters(container);
    translate_and_write_to_file(container, has_flag);
    destroy_container(&container);
}
