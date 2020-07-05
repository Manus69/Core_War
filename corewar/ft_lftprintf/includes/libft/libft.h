/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <selly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:47:07 by selly             #+#    #+#             */
/*   Updated: 2019/10/27 18:52:35 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>

# define BUFF_SIZE 32
# define FD_NUM 20000
# define ERROR -1
# define OK 1

void				ft_putchar(char c);
int					ft_putchar_mod(char c, int *m);
int					ft_strcmp(char const *str1, char const *str2);
size_t				ft_strlen(char const *str);
int					ft_strlen_mod(char const *str);
void				ft_bzero(void *s, size_t n);
void				ft_putstr(char const *str);
int					ft_putstr_mod(char const *str, int fd);
void				*ft_memset(void *src, int c, size_t len);
void				*ft_memcpy(void *dest, void const *src, size_t n);
void				*ft_memccpy(void *dest, void const *src, int c, size_t n);
char				*ft_strdup(char const *str);
void				*ft_memmove(void *dest, void const *src, size_t n);
void				*ft_memchr(void const *s, int c, size_t n);
int					ft_memcmp(void const *s1, void const *s2, size_t n);
char				*ft_strcpy(char *dest, char const *src);
char				*ft_strncpy(char *dest, char const *src, size_t n);
char				*ft_strcat(char *dest, char const *src);
char				*ft_strncat(char *dest, char const *src, size_t n);
size_t				ft_strlcat(char *dest, char const *src, size_t n);
char				*ft_strchr(char const *s, int c);
char				*ft_strrchr(char const *s, int c);
char				*ft_strstr(char const *haystack, char const *needle);
char				*ft_strnstr(char const *h, char const *n, size_t l);
int					ft_strncmp(char const *s1, char const *s2, size_t n);
long				ft_atoi_size_t(char const *s);
int					ft_atoi(char const *c);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);

int					ft_isspace(int c);
int					ft_match(char *s1, char *s2, char point);
int					ft_countwords(char const *str, char c);
int					ft_thebigest_word(char const *str, char c);
char				**ft_strcpymap(char const *s, char **m, char c);

void				*ft_memalloc(size_t size);
void				ft_memdel(void **app);
char				*ft_strnew(size_t size);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
char				*ft_itoa(int n);
char				*ft_itoa_base(int n, int base);
int					ft_atoi_base(const char *str, int base);
char				*ft_itoa_long(unsigned long n);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
int					ft_putnbr_mod(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putendl_fd(char const *s, int fd);

void				ft_sort_word_tab(char **arr);
void				ft_print_char_arr(char const **arr);
char				*ft_stdin(int fd);

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_ch_l
{
	struct s_ch_l	*next;
	char			c;
}					t_char;

t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

char				*ft_cutstr(char *str, int i);
char				*ft_itoa_mod(int num, unsigned int len, int c);
int					ft_print_symbol(int i, char c, int fd);
int					*ft_new_integer_list(int n);
int					ft_char_in_string(char c, char *s);
int					ft_get_integer(const char **p);
int					ft_pow(int i, int x);
int					ft_cut_space(const char **s);
void				ft_numzero(int **s, unsigned int size);
int					ft_length(long long num, int flag);

void				ft_lst_free(t_list **alst);
int					get_next_line(const int fd, char **line);

#endif
