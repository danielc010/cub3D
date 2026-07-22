/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 23:15:24 by lucho             #+#    #+#             */
/*   Updated: 2026/07/22 23:29:59 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *) param;
	free_textures(game);
	mlx_close_window(game->mlx);
	return ;
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		handle_close(param);
}

void	game_loop_hook(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
		ahead_and_back(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
		ahead_and_back(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
		move_sideways(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
		move_sideways(game, 1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		rotate(game, -1);
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		rotate(game, 1);
	raycasting(game);
	return ;
}
