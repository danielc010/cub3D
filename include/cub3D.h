/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 15:54:45 by dachin            #+#    #+#             */
/*   Updated: 2026/07/24 12:41:06 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../../MLX42/include/MLX42/MLX42.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <math.h>
# include <string.h>

# define WIDTH 1280
# define HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
// camera plane length (~66 deg FOV)
# define FOV 0.66
# define COL_MARGIN 0.3

// Texture indices
# define TEX_NO 0
# define TEX_SO 1
# define TEX_EA 2
# define TEX_WE 3

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

// x y: map position (can be fractional, e.g. 1.5)
// dir_x y: direction vector (unit vector)
// plane_x y: camera plane vector (perpendicular to dir)
typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_player;

// grid: grid[row][col], '1'=wall, '0'=empty
// floor_color: 0xRRGGBBAA (MLX42 format)
// tex[4]: indexed by TEX_NO/SO/EA/WE
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

// A's prototypes (parsing)
int			validate_args(int argc, char **argv);
void		error_exit(t_game *game, char *msg);
void		free_grid(t_map *map);
void		free_map(t_map *map);
void		free_game(t_game *game);
char		**list_to_array(t_list *list, t_game *game);
char		**read_lines(int fd, t_game *game);
void		try_tex(t_game *game, char *line, char *id, int index);
void		dispatcher(t_game *game, char **content, int map_start);
void		chk_tex_set(t_game *game);
uint32_t	pack_color(t_game *game, int r, int g, int b);
void		free_char_array(char **array);
void		validate_color_arr(t_game *game, char **array);
void		chk_dup_color(char *line, t_game *game);
char		**extract_chk_color(t_game *game, char *line, int pos);
void		try_color(t_game *game, char *line);
void		chk_color_set(t_game *game);
int			is_all_whitespace(char *line);
int			find_map_start(t_game *game, char **content);
void		parse(t_game *game, char **content);
int			validate_map(char **grid);
void		parse_map(t_game *game, char **map);
void		find_player(t_game *game);
void		free_visited_matrix(char **visited, int rows);
void		flood_fill_reachable(t_game *game, int row,
				int col, char **visited);
void		check_map_enclosed(t_game *game);
int			is_wall(t_map *map, int x, int y);

// B's prototypes (engine)
void		engine_run(t_game *game);
void		init_ray(t_game *game, t_ray *ray, int x);
void		calc_ray_steps(t_game *game, t_ray *ray);
void		dda(t_game *game, t_ray *ray);
void		calc_wall_height(t_ray *ray);
void		render_column(t_game *game, t_ray *ray, int x);
void		raycasting(t_game *game);
void		handle_close(void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		game_loop_hook(void *param);

// Movement
void		ahead_and_back(t_game *game, int sign);
void		move_sideways(t_game *game, int sign);
void		rotate(t_game *game, int sign);

// Textures
void		get_wall_side(t_ray *ray);
void		calc_wall_x(t_game *game, t_ray *ray);
uint32_t	get_texture_color(t_game *game, t_ray *ray, int y);
void		finalize_textures(t_game *game);
void		free_textures(t_game *game);

#endif
