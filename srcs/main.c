/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:03:30 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 13:09:10 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2 || open(av[1], O_RDONLY) == -1)
		return (error_return("cub3d: Wrong argv", 1));
	game = init_game(av[1]);
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WINDOW_W, WINDOW_H, "cub3D");
	game->img.img = mlx_new_image(game->mlx, WINDOW_W, WINDOW_H);
	mlx_hook(game->win, 17, 0, goodbye, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_loop_hook(game->mlx, ft_loop, game);
	mlx_loop(game->mlx);
	free_game(game);
}
