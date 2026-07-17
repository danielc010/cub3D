/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:26:51 by luimarti          #+#    #+#             */
/*   Updated: 2026/07/17 12:43:26 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ahead_and_back(t_game *game, int sign)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.dir_x * MOVE_SPEED * sign;
	new_y = game->player.y + game->player.dir_y * MOVE_SPEED * sign;
	if (game->map.grid[(int)new_y][(int)(new_x + COLLISION_MARGIN)] != '1' &&
		game->map.grid[(int)new_y][(int)(new_x - COLLISION_MARGIN)] != '1' &&
		game->map.grid[(int)(new_y + COLLISION_MARGIN)][(int)(new_x)] != '1' &&
		game->map.grid[(int)(new_y - COLLISION_MARGIN)][(int)(new_x)] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}

void move_sideways(t_game *game, int sign)
{
	double	new_x;
	double	new_y;

	new_x = game->player.x + game->player.plane_x * MOVE_SPEED * sign;
	new_y = game->player.y + game->player.plane_y * MOVE_SPEED * sign;
	if (game->map.grid[(int)new_y][(int)(new_x + COLLISION_MARGIN)] != '1' &&
		game->map.grid[(int)new_y][(int)(new_x - COLLISION_MARGIN)] != '1' &&
		game->map.grid[(int)(new_y + COLLISION_MARGIN)][(int)(new_x)] != '1' &&
		game->map.grid[(int)(new_y - COLLISION_MARGIN)][(int)(new_x)] != '1')
	{
		game->player.x = new_x;
		game->player.y = new_y;
	}
}
