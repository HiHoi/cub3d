/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:36:39 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/10 19:13:18 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	if (keycode == KEY_A)
		game->key.left = 1;
	if (keycode == KEY_D)
		game->key.right = 1;
	if (keycode == KEY_W)
		game->key.up = 1;
	if (keycode == KEY_S)
		game->key.down = 1;
	if (keycode == KEY_ESC)
		exit(0);
	return (0);
}
