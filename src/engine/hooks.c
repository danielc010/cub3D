/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 23:15:24 by lucho             #+#    #+#             */
/*   Updated: 2026/07/06 00:07:58 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	handle_close(void* param)
{
	t_game *game;

	game = (t_game*)param;
	mlx_close_window(game->mlx);
	return ;
}

void	key_hook(mlx_key_data_t keydata, void* param)
{
	t_game *game;

	game = (t_game*)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}
