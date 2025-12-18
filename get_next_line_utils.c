/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloechle <jloechle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:44:44 by jloechle          #+#    #+#             */
/*   Updated: 2025/12/17 11:52:03 by jloechle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	cc;

	cc = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == cc)
		return ((char *) &s[i]);
	return (NULL);
}



size_t	ft_strlen(const	char	*str)
{
	size_t	count;

	count = 0;
	while (*str != '\0')
	{
		str ++;
		count ++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*temp;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (!s)
		return (NULL);
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	temp = ft_calloc(len + 1, sizeof(char));
	if (!temp)
		return (NULL);
	i = 0;
	while (i < len)
	{
		temp[i] = s[start + i];
		i++;
	}
	return (temp);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	tot_len;
	char	*temp;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	tot_len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	temp = malloc(tot_len);
	if (!temp)
		return (NULL);
	temp[0] = '\0';
	ft_strlcat(temp, s1, tot_len);
	ft_strlcat(temp, s2, tot_len);
	return (temp);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	while (i < (nmemb * size))
		p[i++] = 0;
	return (p);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	size_t	i;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	i = 0;
	if (size <= len_dst)
		return (size + len_src);
	while (src[i] && (len_dst + i) < (size - 1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}

char	*gnl_split_line(char **left)
{
	char	*nl;
	char	*line;
	char	*new_left;
	size_t	line_len;
	size_t	rest_len;
	size_t	i;

	if (!left || !*left || (*left)[0] == '\0')
		return (NULL);

	nl = ft_strchr(*left, '\n');
	line_len = nl ? (size_t)(nl - *left) + 1 : ft_strlen(*left);

	line = (char *)malloc(line_len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < line_len)
	{
		line[i] = (*left)[i];
		i++;
	}
	line[i] = '\0';

	if (!nl || nl[1] == '\0')
		return (free(*left), *left = NULL, line);

	rest_len = ft_strlen(nl + 1);
	new_left = (char *)malloc(rest_len + 1);
	if (!new_left)
		return (free(line), NULL);
	i = 0;
	while (i < rest_len)
	{
		new_left[i] = nl[1 + i];
		i++;
	}
	new_left[i] = '\0';

	free(*left);
	*left = new_left;
	return (line);
}


