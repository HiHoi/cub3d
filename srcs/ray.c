/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:42:48 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/11 16:40:51 by hoslim           ###   ########.fr       */
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

void	cal_ray(t_game *game, t_dsable_ray *hv, int horz, int vert)
{
	double	next_touch_x;
	double	next_touch_y;

	next_touch_x = hv->xintercept;
	next_touch_y = hv->yintercept;
	while (next_touch_x >= 0 && next_touch_x <= WINDOW_W \
	&& next_touch_y >= 0 && next_touch_y <= WINDOW_H)
	{
		if (is_wall(game, next_touch_x + vert, next_touch_y + horz))
		{
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

int	modify_value(int check)
{
	if (check == 1)
		return (-1);
	return (0);
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
	cal_ray(game, vert, 0, modify_value(game->ray.is_ray_left));
}

void	cal_horz(t_game *game, t_dsable_ray *horz)
{
	horz->found_wallhit = FALSE;
	horz->wall_hitx = 0;
	horz->wall_hity = 0;
	horz->yintercept = floor(game->player.location.y / TILE_SIZE) * TILE_SIZE;
	// horz->yintercept += game->ray.is_ray_down ? TILE_SIZE : 0;
	if (game->ray.is_ray_down)
		horz->yintercept += TILE_SIZE;
	horz->xintercept = game->player.location.x + (horz->yintercept \
	- game->player.location.y) / tan(game->ray.ray_angle);
	horz->ystep = TILE_SIZE;
	// horz->ystep *= game->ray.is_ray_up ? -1 : 1;
	if (game->ray.is_ray_up)
		horz->ystep *= -1;
	horz->xstep = TILE_SIZE / tan(game->ray.ray_angle);
	// horz->xstep *= (game->ray.is_ray_left && horz->xstep > 0) ? -1 : 1;
	// horz->xstep *= (game->ray.is_ray_right && horz->xstep < 0) ? -1 : 1;
	if (game->ray.is_ray_left && horz->xstep > 0)
		horz->xstep *= -1;
	if (game->ray.is_ray_right && horz->xstep < 0)
		horz->xstep *= -1;
	cal_ray(game, horz, modify_value(game->ray.is_ray_up), 0);
}

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
	// mlx_put_image_to_window(game->mlx, game->win, game->img.img, \
	// (int)(WINDOW_W * (1 - MINISCALE)), (int)(WINDOW_H * (1 - MINISCALE)));
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

void	render_3d(t_game *game, int idx)
{
	int		color;
	int		x;
	int		y;
	int		wall_width;
	double	correct_length = game->ray.distance * cos(game->ray.ray_angle - game->player.rotate_angle);
	double	distace_project_plane = (WINDOW_W / 2) / tan(FOV / 2);
	double	projected_wall_h = (TILE_SIZE / correct_length) * distace_project_plane;
	int		wall_strip_height = (int)projected_wall_h;
	int		wall_top_pixel = (WINDOW_H / 2) - (wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	int		wall_bottom_pixel = (WINDOW_H / 2) + (wall_strip_height / 2);
	if (wall_bottom_pixel > WINDOW_H)
		wall_bottom_pixel = WINDOW_H;
	if (game->ray.was_hit_vert)
		color = 0xFFFFFF;
	else
		color = 0xAAAAAA;
	wall_width = 1;
	y = wall_top_pixel;
	while (y < wall_bottom_pixel)
	{
		x = 0;
		while (x < wall_width)
		{
			if (game->img.data[WINDOW_W * y + (x + idx * wall_width)] == 0x111110)
				game->img.data[WINDOW_W * y + (x + idx * wall_width)] = color;
			x++;
		}
		y++;
	}
	draw_sky(game, idx, wall_bottom_pixel);
	draw_land(game, idx, wall_top_pixel);
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
	// double	max_angle;
	double	ray_range;
	int		i;

	ray_range = FOV;
	angle = game->player.rotate_angle - (ray_range / 2);
	// max_angle = game->player.rotate_angle + (ray_range / 2);
	i = 0;
	while (i < RAY_COUNT)
	{
		draw_one_ray(game, angle, i);
		angle += ray_range / RAY_COUNT;
		i++;
	}
}
