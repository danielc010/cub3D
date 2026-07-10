/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill1.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/10 12:41:10 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/10 18:41:57 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Iterate through and free the array rows and finally the array
static void	free_visited_matrix(char **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		++i;
	}
	free(visited);
}

static void	flood_fill_reachable(t_game *game, int row, int col, char **visited)
{
	if (row < 0 || row >= game->map.rows || col < 0
		|| game->map.grid[row][col] == '\0')
	{
		free_visited_matrix(visited, game->map.rows);
		error_exit(game, "Invalid map, out of bounds");
	}
	if (game->map.grid[row][col] == '1' || visited[row][col] == '1')
		return ;
	if (game->map.grid[row][col] == ' ')
	{
		free_visited_matrix(visited, game->map.rows);
		error_exit(game, "Void area reachable");
	}
	visited[row][col] = '1';
	flood_fill_reachable(game, row - 1, col, visited);
	flood_fill_reachable(game, row + 1, col, visited);
	flood_fill_reachable(game, row, col - 1, visited);
	flood_fill_reachable(game, row, col + 1, visited);
}

static char	**create_visited_matrix(t_game *game, char **map, int rows)
{
	char	**visited;
	int		i;

	visited = ft_calloc(rows, sizeof(char *));
	if (!visited)
		error_exit(game, "Memory allocation failed");
	i = 0;
	while (i < rows)
	{
		visited[i] = ft_calloc(ft_strlen(map[i]) + 1, sizeof(char));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			error_exit(game, "Memory allocation failed");
		}
		++i;
	}
	return (visited);
}

void	check_map_enclosed(t_game *game)
{
	char	**visited;

	visited = create_visited_matrix(game, game->map.grid, game->map.rows);
	flood_fill_reachable(game, (int)game->player.y,
		(int)game->player.x, visited);
	free_visited_matrix(visited, game->map.rows);
}
