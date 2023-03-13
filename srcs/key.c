/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:36:39 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/12 12:33:14 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_A)
		game->player.location.x--;
	if (keycode == KEY_D)
		game->player.location.x++;
	if (keycode == KEY_W)
	{
		if (game->ray.is_ray_up)
			game->player.location.y++;
		else
			game->player.location.y--;
	}
	if (keycode == KEY_S)
	{
		if (game->ray.is_ray_down)
			game->player.location.y--;
		else
			game->player.location.y++;
	}
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_LEFT)
	{
		game->key.left = 1;
		game->key.right = 0;
	}
	if (keycode == KEY_RIGHT)
	{
		game->key.left = 0;
		game->key.right = 1;
	}
	update_player(game);
	return (0);
}
