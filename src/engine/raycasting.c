/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:20:48 by lucho             #+#    #+#             */
/*   Updated: 2026/07/13 23:35:50 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_ray(t_game *game, t_ray *ray, int x)
{
	int	map_x;
	int	map_y;

	map_x = (int)game->player.x;
	map_y = (int)game->player.y;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
    ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
		ray->step_x = -1;
	else
		ray->step_x = 1;
	if (ray->ray_dir_y < 0)
		ray->step_y = -1;
	else
		ray->step_y = 1;

	if (ray->step_x == 1)
    	ray->side_dist_x = (map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (game->player.x - map_x) * ray->delta_dist_x;
	if (ray->step_y == 1)
    	ray->side_dist_y = (map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (game->player.y - map_y) * ray->delta_dist_y;
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		x++;
	}
}
