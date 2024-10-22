/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:54:18 by lpittigl          #+#    #+#             */
/*   Updated: 2024/09/18 15:54:20 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	next_in_list(t_list **current)
{
	t_list	*tmp;

	tmp = (*current)->next;
	free(*current);
	*current = tmp;
}

char	**zero_matrix(int n_lines, int width, t_map *data, t_list *c)
{
	char	**visited;
	int		j;

	j = 0;
	visited = (char **)malloc(n_lines * sizeof(int *));
	if (!visited)
		handle_error(data->map, c, data->y, "Error\nMalloc fail");
	while (j < n_lines)
	{
		visited[j] = (char *)malloc(width + 1 * sizeof(int));
		if (!visited[j])
		{
			destroy_array(visited, j);
			handle_error(data->map, c, data->y, "Error\nMalloc fail");
		}
		ft_bzero(visited[j], width);
		j++;
	}
	return (visited);
}

int	update_lst(t_map *data, t_list **cur, int which, char **visited)
{
	if (which == LEFT || which == RIGHT)
	{
		visited[(*cur)->y][(*cur)->x + which]++;
		if (data->map[(*cur)->y][(*cur)->x + which] == 'E')
			data->exit_flag++;
		ft_lstadd_back(cur, ft_lstnew((*cur)->x + which, (*cur)->y));
		if (data->map[(*cur)->y][(*cur)->x + which] == 'C')
			return (-1);
	}
	else
	{
		visited[(*cur)->y + (which / 2)][(*cur)->x]++;
		if (data->map[(*cur)->y + (which / 2)][(*cur)->x] == 'E')
			data->exit_flag++;
		ft_lstadd_back(cur, ft_lstnew((*cur)->x, (*cur)->y + (which / 2)));
		if (data->map[(*cur)->y + (which / 2)][(*cur)->x] == 'C')
			return (-1);
	}
	return (0);
}

int	is_valid(t_map *data, t_list *c, int n_col)
{
	char	**mem;

	mem = zero_matrix(data->y, data->x, data, c);
	mem[c->y][c->x]++;
	while (c)
	{
		if (c->x - 1 >= 0
			&& mem[c->y][c->x - 1] == '0' && data->map[c->y][c->x - 1] != '1')
			n_col += update_lst(data, &c, LEFT, mem);
		if (c->x + 1 < data->x
			&& mem[c->y][c->x + 1] == '0' && data->map[c->y][c->x + 1] != '1')
			n_col += update_lst(data, &c, RIGHT, mem);
		if (c->y - 1 >= 0
			&& mem[c->y - 1][c->x] == '0' && data->map[c->y - 1][c->x] != '1')
			n_col += update_lst(data, &c, UP, mem);
		if (c->y + 1 < data->y
			&& mem[c->y + 1][c->x] == '0' && data->map[c->y + 1][c->x] != '1')
			n_col += update_lst(data, &c, DOWN, mem);
		next_in_list(&c);
	}
	destroy_array(mem, data->y);
	if (n_col != 0 || data->exit_flag != 1)
		return (0);
	return (1);
}
