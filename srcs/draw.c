/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:51:41 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 13:00:21 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	draw_player(t_game *game)
{
	int	xx;
	int	yy;
	int	row;
	int	col;

	xx = game->player.location.x;
	xx = (int)(MINISCALE * xx);
	yy = game->player.location.y;
	yy = (int)(MINISCALE * yy);
	row = -(game->player.thickness) / 2;
	while (row <= game->player.thickness / 2)
	{
		col = -(game->player.thickness) / 2;
		while (col <= game->player.thickness / 2)
		{
			game->img.data[(int)WINDOW_W * \
			((int)yy + row) + ((int)xx + col)] = 0x0000FF;
			col++;
		}
		row++;
	}
	return (0);
}


int	ft_loop(void *game_void)
{
	t_game	*game;

	game = game_void;
	game->img.data = (int *)mlx_get_data_addr(game->img.img, \
	&(game->img.bpp), &(game->img.line_size), &(game->img.endian));
	render_background(game);
	render_map(game);
	draw_player(game);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	fill_squares(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	x = (int)(MINISCALE * x);
	y = (int)(MINISCALE * y);
	j = 0;
	while (j < (int)(MINISCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINISCALE * TILE_SIZE))
		{
			img->data[(int)WINDOW_W * (y + j) + (i + x)] = color;
			i++;
		}
		j++;
	}
}

void	fill_wall(t_game *game, int wall_bottom, int wall_top, int idx)
{
	int	x;
	int	y;
	int	color;

	if (game->ray.was_hit_vert)
		color = 0xFFFFFF;
	else
		color = 0xAAAAAA;
	y = wall_top;
	while (y < wall_bottom)
	{
		x = 0;
		while (x < WALL_WIDTH)
		{
			if (game->img.data[WINDOW_W * y + (x + idx * WALL_WIDTH)] \
			== 0x111110)
				game->img.data[WINDOW_W * y + (x + idx * WALL_WIDTH)] = color;
			x++;
		}
		y++;
	}
	draw_sky(game, idx, wall_bottom);
	draw_land(game, idx, wall_top);
}
