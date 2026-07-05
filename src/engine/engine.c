/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:38:36 by lucho             #+#    #+#             */
/*   Updated: 2026/07/05 19:00:18 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	engine_run(t_game *game)
{
	int i;
	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (game->mlx == NULL)
		return ;
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img == NULL)
		return ;
	i = mlx_image_to_window(game->mlx, game->img, 0, 0);
	if (i == -1)
		return ;	
	mlx_loop(game->mlx);
}