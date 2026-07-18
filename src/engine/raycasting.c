/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:20:48 by lucho             #+#    #+#             */
/*   Updated: 2026/07/18 21:47:00 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->hit = 0;
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
		ray->side_dist_x = (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	if (ray->step_y == 1)
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
}

void	dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0) //repeat until find a wall
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x = ray->side_dist_x + ray->delta_dist_x;
			ray->map_x = ray->map_x + ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y = ray->side_dist_y + ray->delta_dist_y;
			ray->map_y = ray->map_y + ray->step_y;
			ray->side = 1;
		}
		if (game->map.grid[ray->map_y][ray->map_x] == '1') //if it's a wall..
			ray->hit = 1;
	}
}

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perp_dist);
	ray->draw_start = (HEIGHT / 2) - (ray->line_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	else if (ray->draw_start >= HEIGHT)
		ray->draw_start = HEIGHT - 1;
	ray->draw_end = (HEIGHT / 2) + (ray->line_height / 2);
	if (ray->draw_end < 0)
		ray->draw_end = 0;
	else if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	raycasting(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		dda(game, &ray);
		get_wall_side(&ray);
		calc_wall_height(&ray);
		render_column(game, &ray, x);
		x++;
	}
}
