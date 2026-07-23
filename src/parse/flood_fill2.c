/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:17:45 by dachin            #+#    #+#             */
/*   Updated: 2026/07/23 00:47:38 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
