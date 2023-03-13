/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 12:55:54 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 12:54:13 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	error_return(char *str, int exit)
{
	if (str)
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	return (exit);
}

int	goodbye(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

double	distance_between_point(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

int	is_wall(t_game *game, double x, double y)
{
	int	xx;
	int	yy;

	if (x < 0 || x > WINDOW_W || y < 0 || y > WINDOW_H)
		return (1);
	xx = floor(x / TILE_SIZE);
	yy = floor(y / TILE_SIZE);
	if (game->map[yy][xx] != '0')
		return (1);
	return (0);
}
