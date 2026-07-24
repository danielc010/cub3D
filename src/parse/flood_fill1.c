/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   flood_fill1.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: lucho <lucho@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/07/10 12:41:10 by dachin        #+#    #+#                 */
/*   Updated: 2026/07/24 11:28:34 by dachin        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "parse.h"

// Iterate through and free the array rows and finally the array
void	free_visited_matrix(char **visited, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(visited[i]);
		++i;
	}
	free(visited);
}

static int	flood_fill_push(t_list **stack, int row, int col)
{
	t_point	*new;
	t_list	*node;

	new = ft_calloc(1, sizeof(t_point));
	if (!new)
		return (-1);
	new->row = row;
	new->col = col;
	node = ft_lstnew(new);
	if (!node)
	{
		free(new);
		return (-1);
	}
	ft_lstadd_front(stack, node);
	return (0);
}

static void	flood_fill_pop(t_list **stack, int *row, int *col)
{
	t_list	*temp;

	*row = ((t_point *)(*stack)->content)->row;
	*col = ((t_point *)(*stack)->content)->col;
	temp = *stack;
	*stack = (*stack)->next;
	ft_lstdelone(temp, free);
}

static void	ff_error(t_game *game, char **visited, t_list **stack, char *msg)
{
	free_visited_matrix(visited, game->map.rows);
	ft_lstclear(stack, free);
	error_exit(game, msg);
}

// Iterative recursion where memory is heap allocated instead of stack.
// Recursion risks stack overflow on large maps.
// DFS pattern here - push, pop. validate, mark visited, push neighbours.
// Continues till all reachable floor cells processed or error fires.
void	flood_fill_reachable(t_game *game, int row, int col, char **visited)
{
	t_list	*stack;

	stack = NULL;
	if (flood_fill_push(&stack, row, col) == -1)
		ff_error(game, visited, &stack, "Flood fill failed");
	while (stack)
	{
		flood_fill_pop(&stack, &row, &col);
		if (row < 0 || row >= game->map.rows || col < 0
			|| game->map.grid[row][col] == '\0')
			ff_error(game, visited, &stack,
				"Invalid map, out of bounds");
		if (game->map.grid[row][col] == '1' || visited[row][col] == '1')
			continue ;
		if (game->map.grid[row][col] == ' ')
			ff_error(game, visited, &stack,
				"Void area reachable");
		visited[row][col] = '1';
		if (flood_fill_push(&stack, row - 1, col) == -1
			|| flood_fill_push(&stack, row + 1, col) == -1
			|| flood_fill_push(&stack, row, col - 1) == -1
			|| flood_fill_push(&stack, row, col + 1) == -1)
			ff_error(game, visited, &stack, "Flood fill failed");
	}
}
// TODO: Test this unbounded version of recursion
// static void	flood_fill_reachable(t_game *game,
// int row, int col, char **visited)
// {
// 	if (row < 0 || row >= game->map.rows || col < 0
// 		|| game->map.grid[row][col] == '\0')
// 	{
// 		free_visited_matrix(visited, game->map.rows);
// 		error_exit(game, "Invalid map, out of bounds");
// 	}
// 	if (game->map.grid[row][col] == '1' || visited[row][col] == '1')
// 		return ;
// 	if (game->map.grid[row][col] == ' ')
// 	{
// 		free_visited_matrix(visited, game->map.rows);
// 		error_exit(game, "Void area reachable");
// 	}
// 	visited[row][col] = '1';
// 	flood_fill_reachable(game, row - 1, col, visited);
// 	flood_fill_reachable(game, row + 1, col, visited);
// 	flood_fill_reachable(game, row, col - 1, visited);
// 	flood_fill_reachable(game, row, col + 1, visited);
// }
// t_point is used to pass two int values as one pointer into ft_lstnew
