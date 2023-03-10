/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:14:09 by hoslim            #+#    #+#             */
/*   Updated: 2023/02/23 18:05:03 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	unsigned char	*tmp;
	size_t			i;

	tmp = malloc(elsize * nelem);
	if (!tmp)
		return (0);
	i = 0;
	while (i < elsize)
		tmp[i++] = 0;
	return (tmp);
}

char	**freeall(char **s)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

size_t	word_cnt(const char *s, char c)
{
	size_t	cnt;
	size_t	i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

char	*worddup(const char *s, char c)
{
	size_t	len;
	char	*ptr;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}

char	**ft_split(char const *s, char c)
{
	char	**tmp;
	size_t	i[2];

	i[0] = 0;
	i[1] = 0;
	if (!s)
		return (NULL);
	tmp = (char **)ft_calloc((size_t)word_cnt(s, c) + 1, sizeof(char *));
	if (!tmp)
		return (NULL);
	while (i[0] < (size_t)word_cnt(s, c) && s[i[1]])
	{
		if (s[i[1]] != c)
		{
			tmp[i[0]] = worddup(&s[i[1]], c);
			if (!tmp[i[0]++])
				return (freeall(tmp));
			while (s[i[1]] && s[i[1]] != c)
				i[1]++;
		}
		else
			i[1]++;
	}
	tmp[i[0]] = NULL;
	return (tmp);
}
