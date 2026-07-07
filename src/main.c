/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dachin <dachin@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/06/26 15:54:34 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/08 00:16:54 by dachin        ########   odam.nl         */
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
	dispatcher(&game, content);
	chk_tex_set(&game);
	chk_color_set(&game);
	close(fd);
	return (0);
}
// int main(void)
// {
// 	char *a = "1abc";

// 	printf("sys: %d\n", atoi(a));
// 	printf("libft: %d\n", ft_atoi(a));
// }
