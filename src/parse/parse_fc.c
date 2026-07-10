/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_fc.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/07 14:09:48 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/08 00:45:48 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Shifting a signed int into its sign bit is undefined behavior in C.
// r, g, b are declared as plain int (signed). When r = 255, r << 24 shifts a
// 1 bit into bit position 31 - which is the sign bit of a 32-bit signed
// integer. Hence we cast the numbers to uint32_t before shifting.
uint32_t	pack_color(t_game *game, int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit(game, "Color out of range");
	return (((uint32_t)r << 24) | ((uint32_t)g << 16)
		| ((uint32_t)b << 8) | 0xFF);
}

// check for correct number of color values
// digit check
// empty content check
void	validate_color_arr(t_game *game, char **array)
{
	int	i;
	int	j;

	if (!array[0] || !array[1] || !array[2] || array[3])
		error_exit(game, "Invalid color format");
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (array[i][j])
		{
			if (!ft_isdigit(array[i][j]))
				error_exit(game, "Invalid color format");
			++j;
		}
		++i;
	}
	i = 0;
	while (i < 3)
	{
		if (array[i][0] == '\0')
			error_exit(game, "Invalid color format");
		++i;
	}
}

void	chk_dup_color(char *line, t_game *game)
{
	if (line[0] == 'C')
	{
		if (game->map.ceiling_color != 0)
			error_exit(game, "Duplicate color");
	}
	if (line[0] == 'F')
	{
		if (game->map.floor_color != 0)
			error_exit(game, "Duplicate color");
	}
}

char	**extract_chk_color(t_game *game, char *line, int pos)
{
	char	*value;
	char	**array;

	value = ft_strdup(line + pos);
	if (!value)
		error_exit(game, "Strdup failed");
	array = ft_split(value, ',');
	if (!array)
	{
		free(value);
		error_exit(game, "Split failed");
	}
	free(value);
	validate_color_arr(game, array);
	return (array);
}

// TODO: fix leak on early exit for pack_color
void	try_color(t_game *game, char *line)
{
	int			pos;
	char		**array;
	uint32_t	*target;

	pos = 1;
	if (line[0] == 'C' || line[0] == 'F')
	{
		if (line[1] == ' ' || line[1] == '\t')
		{
			while (line[pos] == ' ' || line[pos] == '\t')
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
