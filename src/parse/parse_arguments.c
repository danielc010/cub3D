/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_arguments.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/06 12:25:58 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/10 18:49:39 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

// Check for number of arguments, file extension, ability to open file
int	validate_args(int argc, char **argv)
{
	size_t	len;
	int		fd;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", 4))
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

// Copy the linked list contents to the array. Free nodes but not content.
char	**list_to_array(t_list *list, t_game *game)
{
	int		size;
	int		i;
	char	**line_array;
	t_list	*cur_node;

	size = ft_lstsize(list);
	line_array = ft_calloc(size + 1, sizeof(char *));
	if (!line_array)
		error_exit(game, "readline fail");
	i = 0;
	while (i < size)
	{
		line_array[i] = list->content;
		cur_node = list;
		list = list->next;
		free(cur_node);
		++i;
	}
	return (line_array);
}

// Store lines read into a linked list, so we know how much to allocate.
// Strip extra trailing \n from end of the line
char	**read_lines(int fd, t_game *game)
{
	t_list	*list;
	char	*line;
	void	*new_node;
	char	**line_array;
	int		len;

	list = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		len = ft_strlen(line);
		if (len != 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		new_node = ft_lstnew(line);
		if (!new_node)
			error_exit(game, "read_line fail");
		ft_lstadd_back(&list, new_node);
	}
	line_array = list_to_array(list, game);
	return (line_array);
}

void	parse(t_game *game, char **content)
{
	int	map_start;

	map_start = find_map_start(game, content);
	dispatcher(game, content, map_start);
	chk_tex_set(game);
	chk_color_set(game);
	parse_map(game, content + map_start);
	find_player(game);
	check_map_enclosed(game);
}

int	is_wall(t_map *map, int x, int y)
{
	if (y < 0 || y >= map->rows || x < 0 || map->grid[y][x] == '\0'
			|| map->grid[y][x] == '1' || map->grid[y][x] == ' ')
		return (1);
	return (0);
}
