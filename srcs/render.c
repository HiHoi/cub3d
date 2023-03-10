/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:08:41 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/10 21:38:06 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_wall(t_game *game, double x, double y)
{
	int	xx;
	int	yy;

	if (x < 0 || x > WINDOW_W || y < 0 || y > WINDOW_H)
		return (1);
	xx = floor(x / TILE_SIZE);
	yy = floor(y / TILE_SIZE);
	if (game->map[yy][xx] != 0)
		return (1);
	return (0);
}

int	update_player(t_game *game)
{
	double	turn_direction;
	double	walk_direction;
	double	new_x;
	double	new_y;
	int		movestep;

	if (game->key.left == 1)
		turn_direction = -1;
	if (game->key.right == 1)
		turn_direction = 1;
	if (game->key.up == 1)
		walk_direction = 1;
	if (game->key.down == 1)
		walk_direction = -1;
	game->player.rotate_angle += turn_direction * game->player.turn_speed;
	movestep = walk_direction * game->player.walk_speed;
	new_x = game->player.location.x + movestep * cos(game->player.rotate_angle);
	new_y = game->player.location.y + movestep * sin(game->player.rotate_angle);
	if (!is_wall(game, new_x, new_y))
	{
		game->player.location.x = new_x;
		game->player.location.y = new_y;
	}
	return (0);
}

int	draw_player(t_game *game)
{
	int	row;
	int	col;

	game->img.data = (int *)mlx_get_data_addr(game->img.img, \
	&(game->img.bpp), &(game->img.line_size), &(game->img.endian));
	row = -(game->player.thickness) / 2;
	while (row <= game->player.thickness / 2)
	{
		col = -(game->player.thickness) / 2;
		while (col <= game->player.thickness / 2)
		{
			game->img.data[(int)(MINISCALE * (WINDOW_W * \
			((int)game->player.location.y + row) \
			+ ((int)game->player.location.x + col)))] = 0x0000FF;
			col++;
		}
		row++;
	}
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, \
	// (int)(WINDOW_W * (1 - MINISCALE)), (int)(WINDOW_H * (1 - MINISCALE)));
	return (0);
}

int	*ft_loop(void *game_void)
{
	t_game	*game;

	game = game_void;
	render_map(game);
	update_player(game);
	draw_player(game);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, \
	(int)(WINDOW_W * (1 - MINISCALE)), (int)(WINDOW_H * (1 - MINISCALE)));
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

void	fill_squares(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < (int)(MINISCALE * TILE_SIZE))
	{
		i = 0;
		while (i < (int)(MINISCALE * TILE_SIZE))
		{
			img->data[(int)(MINISCALE * WINDOW_W) * (y + j) + (i + x)] = color;
			i++;
		}
		j++;
	}
}

void	render_map(t_game *game)
{
	int	col;
	int	row;

	game->img.data = (int *)mlx_get_data_addr(game->img.img, \
	&(game->img.bpp), &(game->img.line_size), &(game->img.endian));
	row = 0;
	while (row < MAP_ROWS)
	{
		col = 0;
		while (col < MAP_COLS)
		{
			if (game->map[row][col] == '1')
				fill_squares(game->img.img, (int)(MINISCALE * TILE_SIZE * col), \
				(int)(MINISCALE * TILE_SIZE * row), 0x000000);
			else
				fill_squares(game->img.img, (int)(MINISCALE * TILE_SIZE * col), \
				(int)(MINISCALE * TILE_SIZE * row), 0xffffff);
			col++;
		}
		row++;
	}
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, \
	// (int)(WINDOW_W * (1 - MINISCALE)), (int)(WINDOW_H * (1 - MINISCALE)));
}
