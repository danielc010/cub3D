/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:54:45 by dachin            #+#    #+#             */
/*   Updated: 2026/07/22 23:53:35 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>

# define WIDTH       1280
# define HEIGHT      720
# define MOVE_SPEED  0.05
# define ROT_SPEED   0.03
# define FOV         0.66

# define COL_MARGIN 0.3

# define TEX_NO  0
# define TEX_SO  1
# define TEX_EA  2
# define TEX_WE  3

typedef enum e_wall_side
{
	NORTH,
	SOUTH,
	EAST,
	WEST
}	t_side;

typedef struct s_texture
{
	mlx_texture_t	*tex;
	uint32_t		*pixels;
	int				width;
	int				height;
}	t_texture;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

typedef struct s_map
{
	char		**grid;
	int			rows;
	int			cols;
	uint32_t	floor_color;
	uint32_t	ceiling_color;
	t_texture	tex[4];
}	t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	t_map		map;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		side;
	int		hit;
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	real_draw_start;
	t_side	wall_side;
	double	wall_x;
}	t_ray;

void		load_debug_map(t_game *g);
void		key_hook(mlx_key_data_t keydata, void *param);
void		game_loop_hook(void *param);

// A's prototypes
void		parse(t_game *game, const char *file);
void		error_exit(t_game *game, const char *msg);
void		free_game(t_game *game);
int			is_wall(t_map *map, int x, int y);

// B's prototypes
void		engine_run(t_game *game);
void		init_ray(t_game *game, t_ray *ray, int x);
void		calc_ray_steps(t_game *game, t_ray *ray);
void		dda(t_game *game, t_ray *ray);
void		calc_wall_height(t_ray *ray);
void		render_column(t_game *game, t_ray *ray, int x);
void		raycasting(t_game *game);
void		handle_close(void *param);

// Movement
void		ahead_and_back(t_game *game, int sign);
void		move_sideways(t_game *game, int sign);
void		rotate(t_game *game, int sign);

//Textures
void		get_wall_side(t_ray *ray);
void		calc_wall_x(t_game *game, t_ray *ray);
uint32_t	get_texture_color(t_game *game, t_ray *ray, int y);
void		load_one_texture(t_texture *texture, char *path);
void		load_textures(t_game *game);
void		free_textures(t_game *game);

#endif
