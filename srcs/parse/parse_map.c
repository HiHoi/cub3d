/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:15:53 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/04 13:50:48 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*parsing_map(int fd)
{
	char	*line;
	char	*all_line;
	char	*tmp;

	all_line = ft_strdup("");
	line = "";
	while (line > 0)
	{
		line = get_next_line(fd);
		if (line == NULL || line[0] == '\n')
			break ;
		
		tmp = all_line;
		all_line = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
	}
	free(line);
	close(fd);
	return (all_line);
}
