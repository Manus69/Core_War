/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tables.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemerald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 20:46:25 by gemerald          #+#    #+#             */
/*   Updated: 2020/07/04 20:47:04 by gemerald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLES_H
# define TABLES_H

# include "op.h"

static const char		*const g_operation_names[] = {"live", "ld", "st", "add",
	"sub", "and", "or", "xor", "zjmp", "ldi", "sti", "fork", "lld", "lldi",
	"lfork", "aff", 0};
static const char		*const g_command_names[] = {".name", ".comment", 0};
static const char		g_separators[] = {'"', '\n',
	COMMENT_CHAR, COMMENT_CHAR_2, SEPARATOR_CHAR, 0};
static const char		g_spaces[] = {' ', '\t', 0};
static const char		g_comment_chars[] = {COMMENT_CHAR, COMMENT_CHAR_2, 0};
static const char		*const g_error_messages[] =\
{"The name size is wrong;\n",
	"The comment size is wrong;\n", "The champ size is wrong;\n",
	"The argument is of the wrong type;\n",
	"The arg count is wrong;\n",
	"The registry number is off;\n",
	"The label is missing;\n", 0};
static const char		*const g_syntax_errors[] =\
{"No new line at the end of file;\n",
	"Name command is missing;\n",
	"Comment command is missing\n", 0};
static const char		*const g_character_errors[] = {"Non ascii character;\n",
	"Null character;\n", "Buffer overflow;\n", 0};

#endif
