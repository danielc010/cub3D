/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/14 19:49:35 by lucho             #+#    #+#             */
/*   Updated: 2026/07/21 12:36:52 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_column(t_game *game, t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		if (y < ray->draw_start)
			mlx_put_pixel(game->img, x, y, game->map.ceiling_color);
		else if (y < ray->draw_end)
			mlx_put_pixel(game->img, x, y, get_texture_color(game, ray, y));
		else
			mlx_put_pixel(game->img, x, y, game->map.floor_color);
		y++;
	}
}
