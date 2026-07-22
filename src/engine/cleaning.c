/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 23:18:50 by lucho             #+#    #+#             */
/*   Updated: 2026/07/22 23:32:18 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_textures(t_game *game)
{
	mlx_delete_texture(game->map.tex[NORTH].tex);
	mlx_delete_texture(game->map.tex[SOUTH].tex);
	mlx_delete_texture(game->map.tex[EAST].tex);
	mlx_delete_texture(game->map.tex[WEST].tex);
}
