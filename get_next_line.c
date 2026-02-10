/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloechle <jloechle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 12:10:15 by jloechle          #+#    #+#             */
/*   Updated: 2026/02/10 15:56:22 by jloechle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_reset(char **s)
{
	if (s && *s)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}

static int	read_to_left(int fd, char **left, char *buf)
{
	ssize_t	br;

	br = 1;
	while (br > 0 && !ft_strchr(*left, '\n'))
	{
		br = read(fd, buf, BUFFER_SIZE);
		if (br < 0)
			return (-1);
		buf[br] = '\0';
		*left = ft_strjoin_free(*left, buf);
		if (!*left)
			return (-1);
	}
	return ((int)br);
}

static char	*split_line(char **left)
{
	char	*nl;
	char	*line;
	char	*new_left;

	if (!*left || (*left)[0] == '\0')
		return (free_reset(left));
	nl = ft_strchr(*left, '\n');
	if (!nl)
	{
		line = ft_strdup(*left);
		free_reset(left);
		return (line);
	}
	line = ft_substr(*left, 0, (size_t)(nl - *left) + 1);
	if (!line)
		return (free_reset(left));
	new_left = ft_strdup(nl + 1);
	free(*left);
	*left = new_left;
	if (*left && (*left)[0] == '\0')
		free_reset(left);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*buf;
	int			br;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (free_reset(&left));
	if (!left)
		left = ft_strdup("");
	if (!left)
		return (NULL);
	buf = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (!buf)
		return (free_reset(&left));
	br = read_to_left(fd, &left, buf);
	free(buf);
	if (br < 0)
		return (free_reset(&left));
	if (br == 0 && left && left[0] == '\0')
		return (free_reset(&left));
	return (split_line(&left));
}

//#include "get_next_line.h"
//#include <fcntl.h>
//#include <stdio.h>

//int main(int argc, char **argv)
//{
//    int     fd;
//    char    *line;

//    if (argc != 2)
//    {
//        printf("Usage: %s <filename>\n", argv[0]);
//        return (1);
//    }

//    fd = open(argv[1], O_RDONLY);
//    if (fd < 0)
//    {
//        printf("Error opening file\n");
//        return (1);
//    }

//    while ((line = get_next_line(fd)) != NULL)
//    {
//        printf("%s", line);
//        free(line);  // Important: free each line after use!
//    }

//    close(fd);
//    return (0);
//}