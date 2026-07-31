/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luimarti <luimarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 21:41:25 by lucho             #+#    #+#             */
/*   Updated: 2026/07/31 10:33:11 by luimarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_wall_side(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x == 1)
			ray->wall_side = WEST;
		else
			ray->wall_side = EAST;
	}
	else
	{
		if (ray->step_y == 1)
			ray->wall_side = NORTH;
		else
			ray->wall_side = SOUTH;
	}
}

/**
 * @brief Computes wall_x: the fraction (0-1) of where along the
 *        wall's width the ray hit.
 *
 * Calculates the exact hit coordinate (player position + perp_dist
 * * ray_dir, on whichever axis varies for this wall orientation),
 * keeps only the decimal part (floor()), and applies a mirror
 * correction on 2 of the 4 possible side/step combinations —
 * without it, textures would render flipped on those faces.
 *
 * @param game Game state (reads player.x/y).
 * @param ray  Ray with perp_dist/wall_side/ray_dir/side/step set.
 */
void	calc_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->wall_side == NORTH || ray->wall_side == SOUTH)
		wall_x = game->player.x + ray->perp_dist * ray->ray_dir_x;
	else
		wall_x = game->player.y + ray->perp_dist * ray->ray_dir_y;
	wall_x = wall_x - floor(wall_x);
	if (ray->side == 0 && ray->step_x == 1)
		wall_x = 1 - wall_x;
	if (ray->side == 1 && ray->step_y == -1)
		wall_x = 1 - wall_x;
	ray->wall_x = wall_x;
}

/**
 * @brief Paints one full screen column: ceiling, textured wall, floor.
 *
 * Loops over all HEIGHT rows for this column, deciding per row
 * whether to paint ceiling, a texture-sampled wall pixel, or floor,
 * based on draw_start/draw_end.
 *
 * @param game Game state (img, ceiling/floor colors).
 * @param ray  Ray with draw_start/draw_end/wall_side/wall_x set.
 * @param x    Screen column being painted.
 */
uint32_t	get_texture_color(t_game *game, t_ray *ray, int y)
{
	t_texture	*texture;
	int			tex_x;
	double		relative_pos;
	int			tex_y;

	texture = &game->map.tex[ray->wall_side];
	tex_x = (int)(ray->wall_x * texture->width);
	relative_pos = (y - ray->real_draw_start) / (double)ray->line_height;
	tex_y = (int)(relative_pos * texture->height);
	if (tex_y < 0)
		tex_y = 0;
	else if (tex_y >= texture->height)
		tex_y = texture->height - 1;
	return (texture->pixels[tex_y * texture->width + tex_x]);
}

void	finalize_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->map.tex[i].width = game->map.tex[i].tex->width;
		game->map.tex[i].height = game->map.tex[i].tex->height;
		game->map.tex[i].pixels = (uint32_t *)game->map.tex[i].tex->pixels;
		i++;
	}
}
