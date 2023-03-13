/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 12:47:50 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 12:49:05 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	cal_ray(game, horz, modify_value(game->ray.is_ray_up), 0);
}
