/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:42:48 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 12:51:51 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_line(t_game *game, double dx, double dy)
{
	double	ray_x;
	double	ray_y;
	int		x;
	int		y;
	double	max_value;

	ray_x = game->player.location.x;
	ray_y = game->player.location.y;
	max_value = fmax(fabs(dx), fabs(dy));
	dx /= max_value;
	dy /= max_value;
	while (1)
	{
		if (!is_wall(game, ray_x, ray_y))
		{
			x = (int)(MINISCALE * ray_x);
			y = (int)(MINISCALE * ray_y);
			game->img.data[WINDOW_W * y + x] = 0xFF0000;
		}
		else
			break ;
		ray_x += dx;
		ray_y += dy;
	}
}

void	draw_sky(t_game *game, int idx, int wall_top)
{
	int	x;
	int	y;

	y = 0;
	while (y < wall_top)
	{
		x = 0;
		while (x < 1)
		{
			if (game->img.data[WINDOW_W * y + (x + idx * 1)] == 0x111110)
				game->img.data[WINDOW_W * y + (x + idx * 1)] = 0x0000FF;
			x++;
		}
		y++;
	}
}

void	draw_land(t_game *game, int idx, int wall_bottom)
{
	int	x;
	int	y;

	y = wall_bottom;
	while (y < WINDOW_H)
	{
		x = 0;
		while (x < 1)
		{
			if (game->img.data[WINDOW_W * y + (x + idx * 1)] == 0x111110)
				game->img.data[WINDOW_W * y + (x + idx * 1)] = 0x00FF00;
			x++;
		}
		y++;
	}

}

void	draw_one_ray(t_game *game, double angle, int i)
{
	t_dsable_ray	horz;
	t_dsable_ray	vert;

	init_ray(&(game->ray), angle);
	cal_horz(game, &horz);
	cal_vert(game, &vert);
	if (vert.distance < horz.distance)
	{
		game->ray.wall_hitx = vert.wall_hitx;
		game->ray.wall_hity = vert.wall_hity;
		game->ray.distance = vert.distance;
		game->ray.was_hit_vert = TRUE;
	}
	else
	{
		game->ray.wall_hitx = horz.wall_hitx;
		game->ray.wall_hity = horz.wall_hity;
		game->ray.distance = horz.distance;
		game->ray.was_hit_vert = FALSE;
	}
	draw_line(game, game->ray.wall_hitx - game->player.location.x, \
	game->ray.wall_hity - game->player.location.y);
	render_3d(game, i);
}

void	draw_ray(t_game *game)
{
	double	angle;
	double	ray_range;
	int		i;

	ray_range = FOV;
	angle = game->player.rotate_angle - (ray_range / 2);
	i = 0;
	while (i < RAY_COUNT)
	{
		draw_one_ray(game, angle, i);
		angle += ray_range / RAY_COUNT;
		i++;
	}
}
