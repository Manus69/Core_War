/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 02:27:21 by selly             #+#    #+#             */
/*   Updated: 2020/06/08 10:34:45 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUAL_H
# define VISUAL_H

# include <ncurses.h>
# include "corewar.h"
# include <stdint.h>
# include <time.h>

# define BORDER					3

# define GREEN					10
# define YELLOW					11
# define RED					12
# define CYAN					13
# define GRAY_SL				14
# define GREEN_SL				15
# define YELLOW_SL				16
# define RED_SL					17
# define CYAN_SL				18
# define LIGHT_YELLOW			19
# define LIGHT_RED				20
# define LIGHT_CYAN				21
# define WHITE					22

static const int			g_color_palette[15] = {
	COLOR_PAIR(WHITE),
	COLOR_PAIR(GREEN),
	COLOR_PAIR(YELLOW),
	COLOR_PAIR(RED),
	COLOR_PAIR(CYAN),
	COLOR_PAIR(GRAY_SL),
	COLOR_PAIR(GREEN_SL),
	COLOR_PAIR(YELLOW_SL),
	COLOR_PAIR(RED_SL),
	COLOR_PAIR(CYAN_SL)
};

void				init_window(WINDOW *win);
WINDOW				*init_win_color(int *key);

#endif
