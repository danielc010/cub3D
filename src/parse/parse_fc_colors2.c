/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_fc_colors2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/12 22:28:11 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/12 22:41:19 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// TODO: fix leak on early exit for pack_color
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
		*target = pack_color(game, ft_atoi(array[0]), ft_atoi(array[1]),
				ft_atoi(array[2]));
		free_char_array(array);
	}
}
