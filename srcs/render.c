/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 16:08:41 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 13:01:50 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void	render_background(t_game *game)
{
	int	col;
	int	row;

	row = 0;
	while (row < WINDOW_H)
	{
		col = 0;
		while (col < WINDOW_W)
		{
			game->img.data[WINDOW_W * row + col] = 0x111110;
			col++;
		}
		row++;
	}
}

void	render_map(t_game *game)
{
	int	col;
	int	row;

	row = 0;
	while (row < MAP_ROWS)
	{
		col = 0;
		while (col < MAP_COLS)
		{
			if (game->map[row][col] == '1')
				fill_squares(game->img.img, (int)(TILE_SIZE * col), \
				(int)(TILE_SIZE * row), 0x000000);
			else
				fill_squares(game->img.img, (int)(TILE_SIZE * col), \
				(int)(TILE_SIZE * row), 0xffffff);
			col++;
		}
		row++;
	}
}

void	render_3d(t_game *game, int idx)
{
	double	correct_length;
	double	distace_project_plane;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;

	correct_length = game->ray.distance * \
	cos(game->ray.ray_angle - game->player.rotate_angle);
	distace_project_plane = (WINDOW_W / 2) / tan(FOV / 2);
	wall_strip_height = (int)((TILE_SIZE / correct_length) \
	* distace_project_plane);
	wall_top_pixel = (WINDOW_H / 2) - (wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (WINDOW_H / 2) + (wall_strip_height / 2);
	if (wall_bottom_pixel > WINDOW_H)
		wall_bottom_pixel = WINDOW_H;
	fill_wall(game, wall_bottom_pixel, wall_top_pixel, idx);
}
