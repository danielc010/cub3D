/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3D.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/26 15:54:45 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/07 00:49:38 by dachin        ########   odam.nl         */
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

# define WIDTH 1280
# define HEIGHT 720
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03
// camera plane length (~66 deg FOV)
# define FOV 0.66

// Texture indices
# define TEX_NO 0
# define TEX_SO 1
# define TEX_EA 2
# define TEX_WE 3

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

int		validate_args(int argc, char **argv);
void	error_exit(t_game *game, char *msg);
void	free_grid(t_map *map);
void	free_map(t_map *map);
void	free_game(t_game *game);
char	**read_lines(int fd, t_game *game);
char	**list_to_array(t_list *list, t_game *game);
void	try_tex(char *line, t_game *game, char *id, int index);
void	chk_tex_set(t_game *game);

#endif
