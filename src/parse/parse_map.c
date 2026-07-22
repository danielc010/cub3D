/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 08:01:56 by dachin            #+#    #+#             */
/*   Updated: 2026/07/23 00:47:55 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	is_all_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			++i;
		else
			return (0);
	}
	return (1);
}

static int	is_line_identifier(char *line)
{
	if (!ft_strncmp(line, "NO ", 3)
		|| !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "WE ", 3)
		|| !ft_strncmp(line, "F ", 2)
		|| !ft_strncmp(line, "C ", 2))
		return (1);
	return (0);
}

// Find starting position of the map in the line array.
int	find_map_start(t_game *game, char **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i][0] == '\0')
		{
			++i;
			continue ;
		}
		else if (is_all_whitespace(content[i]) == 1)
			error_exit(game, "Invalid .cub format, line with only whitespaces");
		else
		{
			if (is_line_identifier(content[i]))
			{
				++i;
				continue ;
			}
			else
				return (i);
		}
	}
	error_exit(game, "Invalid .cub format, no map found");
	return (-1);
}

int	validate_map(char **grid)
{
	int	row;
	int	col;

	row = 0;
	while (grid[row])
	{
		col = 0;
		while (grid[row][col])
		{
			if (grid[row][col] != '0' && grid[row][col] != '1'
				&& grid[row][col] != 'N' && grid[row][col] != 'S'
				&& grid[row][col] != 'E' && grid[row][col] != 'W'
				&& grid[row][col] != ' ')
				return (1);
			++col;
		}
		++row;
	}
	return (0);
}

void	parse_map(t_game *game, char **map)
{
	int	i;

	i = 0;
	while (map[i])
		++i;
	game->map.grid = ft_calloc(i + 1, sizeof(char *));
	if (!game->map.grid)
		error_exit(game, "Grid allocation failed");
	i = 0;
	game->map.rows = 0;
	while (map[i])
	{
		game->map.grid[i] = ft_strdup(map[i]);
		if (!game->map.grid[i])
			error_exit(game, "Strdup for map grid failed");
		++i;
		++game->map.rows;
	}
	if (validate_map(game->map.grid))
		error_exit(game, "Invalid character in map");
}
