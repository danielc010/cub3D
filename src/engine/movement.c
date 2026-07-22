/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:26:51 by luimarti          #+#    #+#             */
/*   Updated: 2026/07/22 23:44:17 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_game *game, int sign)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	angle = ROT_SPEED * sign;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x
		= old_dir_x * cos(angle) - game->player.dir_y * sin(angle);
	game->player.dir_y
		= old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
	game->player.plane_x
		= old_plane_x * cos(angle) - game->player.plane_y * sin(angle);
	game->player.plane_y
		= old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}

int	valid_position(t_game *game, double x, double y)
{
	if (game->map.grid[(int)(y - COL_MARGIN)][(int)(x - COL_MARGIN)] == '1')
		return (0);
	if (game->map.grid[(int)(y - COL_MARGIN)][(int)(x + COL_MARGIN)] == '1')
		return (0);
	if (game->map.grid[(int)(y + COL_MARGIN)][(int)(x - COL_MARGIN)] == '1')
		return (0);
	if (game->map.grid[(int)(y + COL_MARGIN)][(int)(x + COL_MARGIN)] == '1')
		return (0);
	return (1);
}

void	ahead_and_back(t_game *game, int sign)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED * sign;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED * sign;
	if (valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}

void	move_sideways(t_game *game, int sign)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED * sign;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED * sign;
	if (valid_position(game, new_x, game->player.y))
		game->player.x = new_x;
	if (valid_position(game, game->player.x, new_y))
		game->player.y = new_y;
}
