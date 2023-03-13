/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:36:39 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 13:13:20 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_front(t_game *game)
{
	if (game->key.left)
		game->player.location.x--;
	else if (game->key.right)
		game->player.location.x++;
	else if (game->key.up)
		game->player.location.y--;
	else if (game->key.down)
		game->player.location.y++;
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_A)
		game->player.location.x--;
	if (keycode == KEY_D)
		game->player.location.x++;
	if (keycode == KEY_W)
		move_front(game);
	if (keycode == KEY_S)
	{
		if (game->ray.is_ray_down)
			game->player.location.y--;
		else
			game->player.location.y++;
	}
	if (keycode == KEY_LEFT)
	{
		game->key.left = 1;
		game->key.right = 0;
		update_player(game);
	}
	if (keycode == KEY_RIGHT)
	{
		game->key.left = 0;
		game->key.right = 1;
		update_player(game);
	}
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
