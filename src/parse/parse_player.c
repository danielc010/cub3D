/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_player.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucho <lucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/10 11:49:57 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/31 10:22:43 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	count_players(t_game *game, int *x, int *y)
{
	int	row;
	int	col;
	int	players;

	row = 0;
	players = 0;
	while (game->map.grid[row])
	{
		col = 0;
		while (game->map.grid[row][col])
		{
			if (game->map.grid[row][col] == 'N'
				|| game->map.grid[row][col] == 'S'
				|| game->map.grid[row][col] == 'E'
				|| game->map.grid[row][col] == 'W')
			{
				players++;
				*y = row;
				*x = col;
			}
			++col;
		}
		++row;
	}
	return (players);
}

static void	player_details_ns(t_game *game, int y, int x)
{
	char	player_dir;

	player_dir = game->map.grid[y][x];
	if (player_dir == 'N')
	{
		game->player.dir_x = 0;
		game->player.dir_y = -1;
		game->player.plane_x = PLANE_LENGTH;
		game->player.plane_y = 0;
	}
	if (player_dir == 'S')
	{
		game->player.dir_x = 0;
		game->player.dir_y = 1;
		game->player.plane_x = -PLANE_LENGTH;
		game->player.plane_y = 0;
	}
}

static void	player_details_ew(t_game *game, int y, int x)
{
	char	player_dir;

	player_dir = game->map.grid[y][x];
	if (player_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = PLANE_LENGTH;
	}
	if (player_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.dir_y = 0;
		game->player.plane_x = 0;
		game->player.plane_y = -PLANE_LENGTH;
	}
}

// Validate number of players.
// Locate starting position of the player, set directional details.
// Finally set player position in grid to \0, so flood fill does not
// mis-recognise it (only '1', '0', ' '). Grid is also kept clean for renderer.
void	find_player(t_game *game)
{
	int	players;
	int	x;
	int	y;

	players = count_players(game, &x, &y);
	if (players == 0 || players > 1)
		error_exit(game, "Invalid number of players");
	else
	{
		game->player.y = y + 0.5;
		game->player.x = x + 0.5;
	}
	player_details_ns(game, y, x);
	player_details_ew(game, y, x);
	game->map.grid[y][x] = '0';
}
