/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 13:04:07 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/10 20:56:40 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_h(char *str)
{
	int	idx;
	int	ret;

	idx = -1;
	ret = 1;
	while (str[++idx])
	{
		if (str[idx] == '\n')
			ret++;
	}
	return (ret);
}

void	init_player(t_player *player)
{
	player->location.x = WINDOW_W / 2;
	player->location.y = WINDOW_H / 2;
	player->thickness = PLAYER_THICKNESS;
	player->rotate_angle = PI / 2;
	player->walk_speed = 2;
	player->turn_speed = 4 * (PI / 180);
}

void	init_ray(t_ray *ray, double angle)
{
	ray->ray_angle = angle;
	ray->wall_hitx = 0;
	ray->wall_hity = 0;
	ray->distance = 0;
	ray->was_hit_vert = FALSE;
	if (ray->ray_angle > 0 && ray->ray_angle < PI)
	{
		ray->is_ray_down = 1;
		ray->is_ray_up = 0;
	}
	else
	{
		ray->is_ray_down = 0;
		ray->is_ray_up = 1;
	}
	if (ray->ray_angle < 0.5 * PI || ray->ray_angle > 1.5 * PI)
	{
		ray->is_ray_right = 1;
		ray->is_ray_left = 0;
	}
	else
	{
		ray->is_ray_right = 0;
		ray->is_ray_left = 1;
	}
}

t_game	*init_game(char *file)
{
	t_game	*new;
	char	*all_line;
	int		fd;

	new = malloc(sizeof(t_game) * 1);
	fd = open(file, O_RDONLY, 0644);
	//파싱 이후 수정 필요한 부분
	all_line = parsing_map(fd);
	init_player(&new->player);
	new->player_dir.x = -1;
	new->player_dir.y = 0;
	new->plane.x = 0;
	new->plane.y = 0.66;
	new->map = ft_split(all_line, '\n');
	//파싱 이후 수정 필요한 부분
	free(all_line);
	close(fd);
	return (new);
}
