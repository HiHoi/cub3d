/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoslim <hoslim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 20:04:01 by hoslim            #+#    #+#             */
/*   Updated: 2023/03/13 13:07:19 by hoslim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>

# define TRUE 1
# define FALSE 0

# define BUFFER_SIZE 42

# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_UP 	126
# define KEY_DOWN	125

# define PI 3.141592
# define RAY_COUNT (WINDOW_W / 1)
# define WALL_WIDTH 1
# define DBL_MAX __DBL_MAX__
# define FOV 60 * (PI / 180.0)

# define TILE_SIZE 40
# define MINISCALE 0.25
# define MAP_ROWS 12
# define MAP_COLS 20

# define WINDOW_W (MAP_COLS * TILE_SIZE)
# define WINDOW_H (MAP_ROWS * TILE_SIZE)
# define PLAYER_THICKNESS 5

typedef struct s_dsable_ray
{
	double	xintercept;
	double	yintercept;
	double	xstep;
	double	ystep;
	int		found_wallhit;
	double	wall_hitx;
	double	wall_hity;
	double	distance;
}	t_dsable_ray;

typedef struct s_key
{
	int	up;
	int	down;
	int	left;
	int	right;
}	t_key;


typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_player
{
	t_vec	location;
	int		thickness;
	double	rotate_angle;
	double	walk_speed;
	double	turn_speed;
}	t_player;

typedef struct s_img
{
	void	*img;
	int		*data;
	int		bpp;
	int		line_size;
	int		endian;
}	t_img;

typedef struct s_ray
{
	double	ray_angle;
	double	wall_hitx;
	double	wall_hity;
	double	distance;
	int		was_hit_vert;
	int		is_ray_down;
	int		is_ray_up;
	int		is_ray_left;
	int		is_ray_right;
}	t_ray;

typedef struct s_game
{
	void			*win;
	void			*mlx;
	char			**map;
	t_player		player;
	t_vec			player_dir;
	t_vec			plane;
	t_img			img;
	t_key			key;
	t_ray			ray;
}	t_game;

size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, char const *s2);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*get_next_line(int fd);

t_game	*init_game(char *file);
void	init_ray(t_ray *ray, double angle);

int		is_wall(t_game *game, double x, double y);

char	*parsing_map(int fd);
int		goodbye(t_game *game);

void	render_background(t_game *game);
void	render_map(t_game *game);
void	render_3d(t_game *game, int idx);

int		ft_loop(void *game_void);

void	draw_ray(t_game *game);
void	draw_sky(t_game *game, int idx, int wall_top);
void	draw_land(t_game *game, int idx, int wall_bottom);
int		draw_player(t_game *game);
void	fill_squares(t_img *img, int x, int y, int color);
void	fill_wall(t_game *game, int wall_bottom, int wall_top, int idx);

void	cal_distance(t_game *game, t_dsable_ray *hv);
void	cal_ray(t_game *game, t_dsable_ray *hv, int horz, int vert);
void	cal_vert(t_game *game, t_dsable_ray *vert);
void	cal_horz(t_game *game, t_dsable_ray *horz);
double	distance_between_point(double x1, double y1, double x2, double y2);
int		is_wall(t_game *game, double x, double y);

int		update_player(t_game *game);

int		key_press(int keycode, t_game *game);

int		error_return(char *str, int exit);
void	free_game(t_game *game);

#endif
