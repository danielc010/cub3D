/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils1.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/06 14:14:00 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/08 00:00:54 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: add mlx_terminate(game->mlx);
void	error_exit(t_game *game, char *msg)
{
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_game(game);
	exit(1);
}

void	free_grid(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->rows)
	{
		free(map->grid[i]);
		++i;
	}
	free(map->grid);
}

// TODO: look at cleaning up of textures after textures are loaded
void	free_map(t_map *map)
{
	free_grid(map);
}

void	free_game(t_game *game)
{
	free_map(&game->map);
}

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		++i;
	}
	free(array);
}
