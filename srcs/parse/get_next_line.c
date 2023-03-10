/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:06:13 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/04 13:49:17 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	len;

	i = 0;
	len = ft_strlen(src);
	if (size == 0)
		return (len);
	while (i < len && (i + 1) < size)
	{
		*(dest + i) = *(src + i);
		i++;
	}
	if (size > 0)
		*(dest + i) = '\0';
	return (len);
}

char	*make_line(int fd, char *buf, char *back)
{
	int		cnt;
	char	*curptr;

	cnt = 1;
	while (cnt)
	{
		cnt = read(fd, buf, BUFFER_SIZE);
		if (cnt == -1)
			return (NULL);
		else if (cnt == 0)
			break ;
		buf[cnt] = '\0';
		if (!back)
			back = ft_strdup("");
		curptr = back;
		back = ft_strjoin(curptr, buf);
		if (!back)
			return (0);
		free(curptr);
		curptr = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (back);
}

char	*make_back(char *c)
{
	int		i;
	char	*rlt;

	i = 0;
	while (c[i] != '\0' && c[i] != '\n')
		i++;
	if (c[i] == '\0')
		return (0);
	rlt = ft_substr(c, i + 1, ft_strlen(c) - i);
	if (!rlt)
		return (0);
	if (rlt[0] == '\0')
	{
		free(rlt);
		rlt = NULL;
		return (0);
	}
	c[i + 1] = '\0';
	return (rlt);
}

char	*get_next_line(int fd)
{
	static char	*back;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (0);
	line = make_line(fd, buf, back);
	free(buf);
	buf = NULL;
	if (!line)
	{
		free(back);
		back = NULL;
		return (0);
	}
	back = make_back(line);
	return (line);
}
