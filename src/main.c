/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: luimarti <luimarti@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/23 00:32:54 by lucho         #+#    #+#                 */
/*   Updated: 2026/07/31 06:03:21 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_game	game;
	char	**content;
	int		fd;

	ft_bzero(&game, sizeof(game));
	if (validate_args(argc, argv))
		error_exit(&game, "Invalid arguments / argument count");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit(&game, "File open or fd failure");
	content = read_lines(fd, &game);
	parse(&game, content);
	finalize_textures(&game);
	free_char_array(content);
	engine_run(&game);
	return (0);
}
