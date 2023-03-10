/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 15:56:07 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/04 13:49:09 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (tmp == NULL)
		return (0);
	i = 0;
	while (*(src + i))
	{
		*(tmp + i) = *(src + i);
		i++;
	}
	*(tmp + i) = '\0';
	return (tmp);
}

size_t	ft_strlen(const char *str)
{
	int	cnt;

	cnt = 0;
	while (*(str + cnt))
		cnt++;
	return (cnt);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*tmp;

	i = -1;
	j = -1;
	if (s1 == NULL)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tmp = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (tmp == NULL)
		return (0);
	while (s1[++i])
		tmp[i] = s1[i];
	while (s2[++j])
		tmp[i + j] = s2[j];
	tmp[i + j] = '\0';
	s1 = NULL;
	free(s1);
	return (tmp);
}

char	*ft_strchr(const char *str, int c)
{
	char	find;
	int		i;

	i = 0;
	find = (unsigned char)c;
	while (str[i])
	{
		if (str[i] == find)
			return ((char *)&str[i]);
		i++;
	}
	if (str[i] == find)
		return ((char *)&str[i]);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*rlt;

	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start || len == 0)
		return (ft_strdup(""));
	s_len = ft_strlen((char *)(s + start));
	if (ft_strlen(s) < len)
		len = ft_strlen(s);
	if (len > s_len)
		len = s_len;
	rlt = (char *)malloc(sizeof(char) * (len + 1));
	if (rlt == NULL)
		return (0);
	ft_strlcpy(rlt, (char *)(s + start), len + 1);
	return (rlt);
}
