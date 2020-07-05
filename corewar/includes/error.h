/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 01:11:07 by selly             #+#    #+#             */
/*   Updated: 2020/06/08 18:52:35 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define MALLOC_ERROR		"\n\033[0;31mMalloc error.\033[0m\n"
# define FLAG_ERROR			"\n\033[0;31mUnknown argument or file!\033[0m\n"
# define ARGS_ERROR			"\n\033[0;31mInput error!\033[0m\n"
# define PLAYER_ID_ERROR	"\n\033[0;31mWrong player id!\033[0m\n"
# define PLAYER_ERROR		"\n\033[0;31mWrong number of players!\033[0m\n"
# define DUPLICATE_ID_ERROR	"\n\033[0;31mDuplicating player id!\033[0m\n"
# define READ_ERROR			"\n\033[0;31mCan`t open the file!\033[0m\n"
# define NONE_BIN_ERROR		"\n\033[0;31mWrong type of file!\033[0m\n"
# define NO_NULL_ERROR		"\n\033[0;31mNULL separator doesn`t exist!\033[0m\n"
# define SIZE_ERROR			"\n\033[0;31mWrong size of player`s code!\033[0m\n"
# define CODE_SIZE_ERROR	"\n\033[0;31mWrong size of champion file!\033[0m\n"

#endif
