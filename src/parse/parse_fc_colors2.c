/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_fc_colors2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucho <lucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/12 22:28:11 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/24 10:55:40 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static uint32_t	color_helper(t_game *game, char **array)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(array[0]);
	g = ft_atoi(array[1]);
	b = ft_atoi(array[2]);
	free_char_array(array);
	return (pack_color(game, r, g, b));
}

void	try_color(t_game *game, char *line)
{
	int			pos;
	char		**array;
	uint32_t	*target;

	pos = 1;
	if (line[0] == 'C' || line[0] == 'F')
	{
		if (line[1] == ' ')
		{
			while (line[pos] == ' ')
				++pos;
		}
		else
			error_exit(game, "Invalid color format");
		chk_dup_color(line, game);
		array = extract_chk_color(game, line, pos);
		if (line[0] == 'F')
			target = &game->map.floor_color;
		if (line[0] == 'C')
			target = &game->map.ceiling_color;
		*target = color_helper(game, array);
	}
}
