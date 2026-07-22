/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 21:41:25 by lucho             #+#    #+#             */
/*   Updated: 2026/07/22 23:15:36 by lucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (ray->side == 0 && ray->step_x == -1)
		wall_x = 1 - wall_x;
	ray->wall_x = wall_x;
}

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

void	load_one_texture(t_texture *texture, char *path)
{
	texture->tex = mlx_load_png(path);
	if (texture->tex == NULL)
	{
		printf("Error: %s\n", mlx_strerror(mlx_errno));
		exit(EXIT_FAILURE);
	}
	texture->width = texture->tex->width;
	texture->height = texture->tex->height;
	texture->pixels = (uint32_t *)texture->tex->pixels;
}

void	load_textures(t_game *game)
{
	load_one_texture(&game->map.tex[NORTH], "textures/brick.png");
	load_one_texture(&game->map.tex[SOUTH], "textures/thornfloor_damp.png");
	load_one_texture(&game->map.tex[EAST], "textures/grass.png");
	load_one_texture(&game->map.tex[WEST], "textures/cliff_ice.png");
}
