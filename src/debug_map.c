/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:10:16 by lucho             #+#    #+#             */
/*   Updated: 2026/07/16 23:21:43 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_game *g)
{
	g->player.x = 1.5;
	g->player.y = 1.5;
	g->player.dir_x = 1.0;
	g->player.dir_y = 0.0;
	g->player.plane_x = 0.0;
	g->player.plane_y = 0.66;
}

void	load_debug_map(t_game *g)
{
	static char	*grid[] = {
		"111111",
		"100001",
		"101001",
		"100001",
		"111111",
		NULL
	};

	g->map.grid = grid;
	g->map.rows = 5;
	g->map.cols = 6;
	g->map.ceiling_color = 0x0000FFFF;
	g->map.floor_color = 0x00FF00FF;
	init_player(g);
}
