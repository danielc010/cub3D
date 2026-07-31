/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/06 22:20:48 by lucho             #+#    #+#             */
/*   Updated: 2026/07/31 10:33:01 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * @brief Sets up a ray's initial direction and map position.
 *
 * Computes camera_x (this column's position in the FOV, -1 to 1),
 * combines it with dir/plane to get ray_dir_x/y (this ray's exact
 * direction), and finds the player's current integer map cell.
 * Delegates delta_dist/step/side_dist to calc_ray_steps().
 *
 * @param game Game state (reads player.dir/plane/x/y).
 * @param ray  Ray to initialize.
 * @param x    Screen column (0 to WIDTH-1).
 */
void	init_ray(t_game *game, t_ray *ray, int x)
{
	ray->map_x = (int)game->player.x;
	ray->map_y = (int)game->player.y;
	ray->hit = 0;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * ray->camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * ray->camera_x;
	calc_ray_steps(game, ray);
}

/**
 * @brief Computes DDA setup values: delta_dist, step, side_dist.
 *
 * delta_dist_x/y: distance to cross one full cell on that axis.
 * step_x/y: +1 or -1, based on the sign of ray_dir_x/y.
 * side_dist_x/y: distance to the FIRST grid line to cross, since
 * the player is rarely exactly on a cell boundary.
 *
 * @param game Game state (reads player.x/y for side_dist).
 * @param ray  Ray with ray_dir_x/y and map_x/y already set.
 */
void	calc_ray_steps(t_game *game, t_ray *ray)
{
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
		ray->side_dist_x
			= (ray->map_x + 1.0 - game->player.x) * ray->delta_dist_x;
	else
		ray->side_dist_x = (game->player.x - ray->map_x) * ray->delta_dist_x;
	if (ray->step_y == 1)
		ray->side_dist_y
			= (ray->map_y + 1.0 - game->player.y) * ray->delta_dist_y;
	else
		ray->side_dist_y = (game->player.y - ray->map_y) * ray->delta_dist_y;
}

/**
 * @brief Walks the ray cell by cell until it hits a wall.
 *
 * Each iteration: compares side_dist_x vs side_dist_y, crosses
 * whichever grid line is closer, advances that axis's map
 * coordinate and side_dist counter, and records which axis was
 * crossed in `side` (0=vertical, 1=horizontal). Stops when the
 * new cell in game->map.grid is a wall ('1').
 *
 * @param game Game state (reads map.grid for wall detection).
 * @param ray  Ray with delta_dist/step/side_dist already set.
 */
void	dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
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
		if (game->map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

/**
 * @brief Converts the DDA result into an on-screen wall height.
 *
 * perp_dist: undoes the DDA's one-step overshoot (side_dist minus
 * delta_dist), giving the distance perpendicular to the player's
 * facing direction rather than the ray's own diagonal length —
 * this avoids the fish-eye effect (curved walls at screen edges).
 * line_height: inversely proportional to perp_dist (closer = taller).
 * draw_start/draw_end: the strip centered on HEIGHT/2 (eye level),
 * clamped to valid screen rows. real_draw_start keeps the unclamped
 * value for later texture-row sampling (see get_texture_color).
 *
 * @param ray Ray with side_dist/delta_dist/side already set by dda().
 */
void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perp_dist);
	ray->real_draw_start = (HEIGHT / 2.0) - (ray->line_height / 2.0);
	ray->draw_start = (int)ray->real_draw_start;
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

/**
 * @brief Renders one full frame: one ray per screen column.
 *
 * For each column x (0 to WIDTH-1): builds the ray (init_ray),
 * walks it to a wall (dda), determines the hit face (get_wall_side),
 * computes its screen height (calc_wall_height), locates the exact
 * texture point (calc_wall_x), and paints the column (render_column).
 * Runs once per frame, called from game_loop_hook after input.
 *
 * @param game Game state.
 */
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
		calc_wall_x(game, &ray);
		render_column(game, &ray, x);
		x++;
	}
}
