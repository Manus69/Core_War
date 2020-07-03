/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selly <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/11 15:43:19 by selly             #+#    #+#             */
/*   Updated: 2019/05/22 16:42:37 by selly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_line(char **buffer, char **line)
{
	char	*tmp_buf;
	char	*get_new_line;
	int		count;

	count = 0;
	get_new_line = *buffer;
	while (get_new_line[count] != '\n')
		if (!get_new_line[count++])
			return (0);
	tmp_buf = &get_new_line[count];
	*tmp_buf = '\0';
	*line = ft_strdup(*buffer);
	*buffer = ft_strdup(tmp_buf + 1);
	free(get_new_line);
	get_new_line = NULL;
	return (OK);
}

static int		read_file(int fd, char *string, char **buffer, char **line)
{
	int		is_read;
	char	*tmp_buf;

	while ((is_read = read(fd, string, BUFF_SIZE)) > 0)
	{
		string[is_read] = '\0';
		if (*buffer)
		{
			tmp_buf = *buffer;
			*buffer = ft_strjoin(tmp_buf, string);
			free(tmp_buf);
			tmp_buf = NULL;
		}
		else
			*buffer = ft_strdup(string);
		if (get_line(buffer, line))
			break ;
	}
	return (is_read > 0 ? 1 : is_read);
}

int				get_next_line(const int fd, char **line)
{
	static char		*fd_buffer[FD_NUM];
	char			*new;
	int				is_read;

	if (!line || (fd < 0 || fd > FD_NUM) || (read(fd, fd_buffer[fd], 0) < 0) \
			|| !(new = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (ERROR);
	if (fd_buffer[fd])
		if (get_line(&fd_buffer[fd], line))
			return (OK);
	ft_bzero(new, BUFF_SIZE + 1);
	is_read = read_file(fd, new, &fd_buffer[fd], line);
	free(new);
	if (is_read != 0 || fd_buffer[fd] == NULL || fd_buffer[fd][0] == '\0')
	{
		if (!is_read && *line)
			*line = NULL;
		return (is_read);
	}
	*line = fd_buffer[fd];
	fd_buffer[fd] = NULL;
	return (OK);
}
