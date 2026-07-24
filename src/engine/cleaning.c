/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucho <lucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/22 23:18:50 by lucho         #+#    #+#                 */
/*   Updated: 2026/07/24 11:45:21 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_textures(t_game *game)
{
	mlx_delete_texture(game->map.tex[NORTH].tex);
	game->map.tex[NORTH].tex = NULL;
	mlx_delete_texture(game->map.tex[SOUTH].tex);
	game->map.tex[SOUTH].tex = NULL;
	mlx_delete_texture(game->map.tex[EAST].tex);
	game->map.tex[EAST].tex = NULL;
	mlx_delete_texture(game->map.tex[WEST].tex);
	game->map.tex[WEST].tex = NULL;
}
