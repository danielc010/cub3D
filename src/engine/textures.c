/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucho <lucho@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/18 21:41:25 by lucho             #+#    #+#             */
/*   Updated: 2026/07/18 21:44:52 by lucho            ###   ########.fr       */
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
