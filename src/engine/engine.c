/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 18:38:36 by lucho             #+#    #+#             */
/*   Updated: 2026/07/24 13:47:28 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	engine_run(t_game *game)
{
	int	i;

	game->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (game->mlx == NULL)
		return ;
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->img == NULL)
	{
		mlx_terminate(game->mlx);
		return ;
	}
	i = mlx_image_to_window(game->mlx, game->img, 0, 0);
	if (i == -1)
		return ;
	mlx_loop_hook(game->mlx, game_loop_hook, game);
	mlx_close_hook(game->mlx, handle_close, game);
	mlx_key_hook(game->mlx, key_hook, game);
	mlx_loop(game->mlx);
	mlx_terminate(game->mlx);
	free_game(game);
}
