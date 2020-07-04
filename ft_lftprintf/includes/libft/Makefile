# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: selly <selly@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/05 18:02:08 by selly             #+#    #+#              #
#    Updated: 2020/07/04 21:25:25 by gemerald         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRC =	ft_memset.c				\
		ft_bzero.c				\
		ft_memcpy.c				\
		ft_memccpy.c			\
		ft_memmove.c			\
		ft_memchr.c				\
		ft_memcmp.c				\
		ft_strlen.c				\
		ft_strdup.c				\
		ft_strcpy.c				\
		ft_strncpy.c			\
		ft_strcat.c				\
		ft_strncat.c			\
		ft_strlcat.c			\
		ft_strchr.c				\
		ft_strrchr.c			\
		ft_strstr.c				\
		ft_strnstr.c			\
		ft_strcmp.c				\
		ft_strncmp.c			\
		ft_atoi.c				\
		ft_atoi_size_t.c		\
		ft_isalpha.c			\
		ft_isdigit.c			\
		ft_isalnum.c			\
		ft_isascii.c			\
		ft_isprint.c			\
		ft_toupper.c			\
		ft_tolower.c			\
								\
		ft_thebigest_word.c		\
		ft_countwords.c			\
		ft_isspace.c			\
		ft_strcpymap.c			\
								\
		ft_memalloc.c			\
		ft_memdel.c				\
		ft_strnew.c				\
		ft_strdel.c				\
		ft_strclr.c				\
		ft_striter.c			\
		ft_striteri.c			\
		ft_strmap.c				\
		ft_strmapi.c			\
		ft_strequ.c				\
		ft_strnequ.c			\
		ft_strsub.c				\
		ft_strjoin.c			\
		ft_strtrim.c			\
		ft_strsplit.c			\
		ft_itoa.c				\
		ft_itoa_base.c			\
		ft_match.c				\
		ft_sort_word_tab.c		\
		ft_atoi_base.c			\
		ft_itoa_long.c			\
		ft_putchar.c			\
		ft_putstr.c				\
		ft_putendl.c			\
		ft_putnbr.c				\
		ft_putchar_fd.c			\
		ft_putstr_fd.c			\
		ft_putendl_fd.c			\
		ft_putnbr_fd.c			\
								\
		ft_lstnew.c				\
		ft_lstdelone.c			\
		ft_lstdel.c				\
		ft_lstadd.c				\
		ft_lstiter.c			\
		ft_lstmap.c				\
								\
		ft_cutstr.c				\
		ft_itoa_mod.c			\
		ft_print_symbol.c		\
		ft_new_integer_list.c	\
		ft_char_in_string.c		\
		ft_get_integer.c		\
		ft_pow.c				\
		ft_cut_space.c			\
		ft_numzero.c			\
		ft_length.c				\
								\
		ft_putchar_mod.c		\
		ft_putnbr_mod.c			\
		ft_putstr_mod.c			\
		ft_strlen_mod.c			\
								\
		ft_lst_free.c 			\
		ft_print_char_arr.c 	\
		ft_stdin.c				\
								\
		get_next_line.c 		\

FLAGS = gcc -c -Wall -Wextra -Werror
OBJ = $(SRC:.c=.o)

HEADER := libft.h

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ) : %.o: %.c $(HEADER)
	$(FLAGS) -o $@ -c $<

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
