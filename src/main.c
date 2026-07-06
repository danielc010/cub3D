/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/26 15:54:34 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/06 16:54:47 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	main(int argc, char **argv)
{
	char	**content;
	int		fd;
	t_game	game;

	ft_bzero(&game, sizeof(game));
	if (validate_args(argc, argv))
		error_exit(&game, "Invalid arguments / argument count");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		error_exit(&game, "File open or fd failure");
	content = (read_lines(fd, &game));
	int i = 0;
	// DEBUG
	while (content[i])
	{
		printf("%s", content[i]);
		++i;
	}
	close(fd);
	return (0);
}
