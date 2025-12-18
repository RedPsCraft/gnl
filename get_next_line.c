/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloechle <jloechle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:10:15 by jloechle          #+#    #+#             */
/*   Updated: 2025/12/18 13:14:54 by jloechle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static char	*fill_line(int fd, char **left_c, char *buffer);
static char	*set_line(char *line_buff);
char	*gnl_join_free(char *s1, char *s2);

char	*get_next_line(int fd)
{
	char			*buffer;
	static char		*left_c;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(left_c);
		left_c = NULL;
		return (NULL);
	}

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);

	line = fill_line(fd, &left_c, buffer);
	free(buffer);
	return (line);
}

static int	read_to_left(int fd, char **left_c, char *buffer)
{
	ssize_t	br;

	br = 1;
	while (br > 0 && !ft_strchr(*left_c, '\n'))
	{
		br = read(fd, buffer, BUFFER_SIZE);
		if (br < 0)
			return (-1);
		buffer[br] = '\0';
		*left_c = gnl_join_free(*left_c, buffer);
		if (!*left_c)
			return (-1);
	}
	return ((int)br);
}

static	char	*extract_line_and_update_left(char **left_c)
{
	char	*line;
	char	*tmp;

	if ((*left_c)[0] == '\0')
		return (NULL);
	tmp = ft_strdup(*left_c);
	if (!tmp)
		return (NULL);
	free(*left_c);
	*left_c = set_line(tmp);
	line = tmp;
	return (line);
}

static	char	*fill_line(int fd, char **left_c, char *buffer)
{
	int	br;

	if (!*left_c)
		*left_c = ft_strdup("");
	if (!*left_c)
		return (NULL);
	br = read_to_left(fd, left_c, buffer);
	if (br < 0)
		return (free(*left_c), *left_c = NULL, NULL);
	if (br == 0 && (*left_c)[0] == '\0')
		return (free(*left_c), *left_c = NULL, NULL);
	return (extract_line_and_update_left(left_c));
}


static char	*set_line(char *line_buff)
{
	ssize_t	i;
	char	*left_c;

	i = 0;
	while (line_buff[i] != '\n' && line_buff[i] != '\0')
		i++;


	if (line_buff[i] == '\0')
		return (NULL);
	if (line_buff[i + 1] == '\0')
	{
		line_buff[i + 1] = '\0';
		return (NULL);
	}

	left_c = ft_substr(line_buff, i + 1, ft_strlen(line_buff) - (i + 1));
	if (left_c && *left_c == '\0')
	{
		free(left_c);
		left_c = NULL;
	}
	line_buff[i + 1] = '\0';
	return (left_c);
}

{char	*gnl_join_free(char *s1, char *s2)

	char	*res;

	if (!s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}
