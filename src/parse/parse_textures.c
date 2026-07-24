/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_textures.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucho <lucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/07 14:08:23 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/24 12:24:36 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// If identifier matches, check for valid format, dup then load texture.
void	try_tex(t_game *game, char *line, char *id, int index)
{
	mlx_texture_t	*texture;
	char			*path;
	int				pos;

	pos = 2;
	if (!ft_strncmp(line, id, 2))
	{
		if (line[2] == ' ')
		{
			while (line[pos] == ' ')
				++pos;
		}
		else
			error_exit(game, "Invalid texture format");
		if (game->map.tex[index].tex != NULL)
			error_exit(game, "Duplicate texture");
		path = ft_strdup(line + pos);
		if (!path)
			error_exit(game, "Strdup failed");
		texture = mlx_load_png(path);
		if (texture == NULL)
			error_exit(game, "Texture loading failed");
		free(path);
		game->map.tex[index].tex = texture;
	}
}

void	dispatcher(t_game *game, char **content, int map_start)
{
	int	i;

	i = 0;
	while (i < map_start)
	{
		try_tex(game, content[i], "NO", TEX_NO);
		try_tex(game, content[i], "SO", TEX_SO);
		try_tex(game, content[i], "EA", TEX_EA);
		try_tex(game, content[i], "WE", TEX_WE);
		try_color(game, content[i]);
		++i;
	}
}

// Check that all textures have been set (game was initialised with ft_bzero).
void	chk_tex_set(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->map.tex[i].tex == NULL)
			error_exit(game, "Not all textures set");
		++i;
	}
}

// Check that all colors have been set (game was initialised with ft_bzero).
void	chk_color_set(t_game *game)
{
	if (game->map.floor_color == 0 || game->map.ceiling_color == 0)
		error_exit(game, "Not all colors set");
}

int	is_wall(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->rows || x < 0 || map->grid[y][x] == '\0'
			|| map->grid[y][x] == '1' || map->grid[y][x] == ' ')
		return (1);
	return (0);
}
