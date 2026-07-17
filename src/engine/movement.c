/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/17 11:26:51 by luimarti          #+#    #+#             */
/*   Updated: 2026/07/17 17:05:47 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate(t_game *game, int sign)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	angle = ROT_SPEED * sign; //ROT_SPEED es exactamente cuantos radianes gira la camara cada vez que se procesa un frame al pulsa runa tecla.
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y * sin(angle); // formula de matriz de rotacion 2d: x' = x·cos(α) - y·sin(α) ; y' = x·sin(α) + y·cos(α)
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
	game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);

}

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
