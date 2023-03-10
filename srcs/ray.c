/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:42:48 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/10 21:59:57 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	distance_between_point(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cal_distance(t_game *game, t_dsable_ray *hv)
{
	if (hv->found_wallhit == TRUE)
		hv->distance = distance_between_point(game->player.location.x, \
		game->player.location.y, hv->wall_hitx, hv->wall_hity);
	else
		hv->distance = DBL_MAX;
}

void	cal_ray(t_game *game, t_dsable_ray *hv)
{
	double	next_touch_x;
	double	next_touch_y;
	int		tmp;

	next_touch_x = hv->xintercept;
	next_touch_y = hv->yintercept;
	while (next_touch_x >= 0 && next_touch_x <= WINDOW_W \
	&& next_touch_y >= 0 && next_touch_y <= WINDOW_H)
	{
		if (game->ray.is_ray_up)
			tmp = 1;
		else
			tmp = 0;
		if (is_wall(game, next_touch_x, next_touch_y - tmp))
		{
			printf("!\n");
			hv->found_wallhit = TRUE;
			hv->wall_hitx = next_touch_x;
			hv->wall_hity = next_touch_y;
			break ;
		}
		else
		{
			next_touch_x += hv->xstep;
			next_touch_y += hv->ystep;
		}
	}
	cal_distance(game, hv);
}

void	cal_vert(t_game *game, t_dsable_ray *vert)
{
	vert->found_wallhit = FALSE;
	vert->wall_hitx = 0;
	vert->wall_hity = 0;
	vert->xintercept = floor(game->player.location.x / TILE_SIZE) * TILE_SIZE;
	if (game->ray.is_ray_right)
		vert->xintercept += TILE_SIZE;
	vert->yintercept = game->player.location.y + (vert->xintercept \
	- game->player.location.x) * tan(game->ray.ray_angle);
	vert->xstep = TILE_SIZE;
	if (game->ray.is_ray_left)
		vert->xstep *= -1;
	vert->ystep = TILE_SIZE * tan(game->ray.ray_angle);
	if (game->ray.is_ray_up && vert->ystep > 0)
		vert->ystep *= -1;
	if (game->ray.is_ray_down && vert->ystep < 0)
		vert->ystep *= -1;
	cal_ray(game, vert);
}

void	cal_horz(t_game *game, t_dsable_ray *horz)
{
	horz->found_wallhit = FALSE;
	horz->wall_hitx = 0;
	horz->wall_hity = 0;
	horz->yintercept = floor(game->player.location.y / TILE_SIZE) * TILE_SIZE;
	if (game->ray.is_ray_down)
		horz->yintercept += TILE_SIZE;
	horz->xintercept = game->player.location.x + (horz->yintercept \
	- game->player.location.y) / tan(game->ray.ray_angle);
	horz->ystep = TILE_SIZE;
	if (game->ray.is_ray_up)
		horz->ystep *= -1;
	horz->xstep = TILE_SIZE / tan(game->ray.ray_angle);
	if (game->ray.is_ray_left && horz->xstep > 0)
		horz->xstep *= -1;
	if (game->ray.is_ray_right && horz->xstep < 0)
		horz->xstep *= -1;
	cal_ray(game, horz);
}

void	draw_line(t_game *game, t_player *player, t_ray *ray)
{
	double	ray_x;
	double	ray_y;
	double	dx;
	double	dy;
	double	max_value;

	ray_x = game->player.location.x;
	ray_y = game->player.location.y;
	dx = ray->wall_hitx - player->location.x;
	dy = ray->wall_hity - player->location.y;
	max_value = fmax(fabs(dx), fabs(dy));
	dx /= max_value;
	dy /= max_value;
	game->img.data = (int *)mlx_get_data_addr(game->img.img, \
	&(game->img.bpp), &(game->img.line_size), &(game->img.endian));
	while (1)
	{
		if (!is_wall(game, ray_x, ray_y))
			game->img.data[WINDOW_W * (int)floor(ray_y) + (int)floor(ray_x)] \
			= 0x00FF00;
		else
			break ;
		ray_x += dx;
		ray_y += dy;
	}
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, \
	// (int)(WINDOW_W * (1 - MINISCALE)), (int)(WINDOW_H * (1 - MINISCALE)));
}

void	draw_one_ray(t_game *game, double angle)
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
	draw_line(game, &game->player, &game->ray);
}

void	draw_ray(t_game *game)
{
	double	angle;
	double	max_angle;
	double	ray_range;

	angle = game->player.rotate_angle;
	ray_range = PI / 3.0;
	max_angle = game->player.rotate_angle + (ray_range / 2);
	while (angle <= max_angle)
	{
		draw_one_ray(game, angle);
		draw_one_ray(game, angle - (ray_range / 2));
		angle += (ray_range / 2.0) / ((RAY_COUNT - 1) / 2.0);
	}
}
