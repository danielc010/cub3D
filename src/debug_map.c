/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:10:16 by lucho             #+#    #+#             */
/*   Updated: 2026/07/21 19:31:51 by lucho            ###   ########.fr       */
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
		"1111111111",
		"1000000001",
		"1000010001",
		"1000010001",
		"1001010001",
		"1001110001",
		"1000000001",
		"1000000001",
		"1000000001",
		"1111111111",
		NULL
	};

	g->map.grid = grid;
	g->map.rows = 5;
	g->map.cols = 6;
	g->map.ceiling_color = 0x6B8CAEFF;
	g->map.floor_color = 0x8A9B6EFF;
	init_player(g);
}
