/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 14:55:50 by lpittigl          #+#    #+#             */
/*   Updated: 2024/09/16 14:55:52 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_walls(char *c, int y, int n_lines)
{
	int	i;

	i = 0;
	if (c[0] == 0)
		return (1);
	while (c[i])
	{
		if (c[i] != WALL && c[i] != PLAYER && c[i] != COLL
			&& c[i] != GROUND && c[i] != EXIT)
			return (0);
		if (y == 0 || y == n_lines - 1)
			if (c[i] != WALL)
				return (0);
		i++;
	}
	if (c[0] != WALL || c[i - 1] != WALL)
		return (0);
	return (1);
}

char	**init_map(char *file_name, int n_lines, t_list *entrance, int x)
{
	char	**map;
	int		i;
	int		fd;
	int		flag;

	i = 0;
	flag = 0;
	fd = open(file_name, O_RDONLY);
	map = (char **)malloc(n_lines * sizeof(char *));
	while (i < n_lines)
	{
		map[i] = get_next_line(fd);
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = 0;
		if (!check_walls(map[i], i, n_lines) || ft_strlen(map[i]) != x)
			flag++;
		i++;
	}
	free(get_next_line(fd));
	close (fd);
	if (flag != 0)
		handle_error(map, entrance, n_lines, "Error\nInvalid map");
	return (map);
}

t_list	*read_map(t_map *data, int x, int fd, char *temp)
{
	t_list	*entrance;

	entrance = NULL;
	data->x = ft_strlen(temp) - 1;
	while (temp)
	{
		x = 0;
		while (temp[x])
		{
			if (temp[x] == PLAYER && data->n_entr++ == 0)
				entrance = ft_lstnew(x, data->y);
			if (temp[x] == EXIT)
				data->n_exit++;
			if (temp[x++] == COLL)
				data->n_col++;
		}
		free(temp);
		temp = get_next_line(fd);
		data->y++;
	}
	close (fd);
	return (entrance);
}

int	main(int argc, char **argv)
{
	t_list	*entrance;
	t_map	data;
	int		fd;
	char	*temp;

	if (argc != 2)
		handle_error(NULL, NULL, 0, "Error\nInvalid input");
	check_file(argv[1]);
	data = set_data();
	fd = open (argv[1], O_RDONLY);
	temp = get_next_line(fd);
	if (!temp)
		handle_error(NULL, NULL, 0, "Error\nEmpty or non existent file");
	entrance = read_map(&data, 0, fd, temp);
	if (data.y == 0 || !entrance || data.n_entr != 1
		|| data.n_exit != 1 || data.n_col < 1)
		handle_error(NULL, entrance, data.y, "Error\nInvalid map");
	data.map = init_map(argv[1], data.y, entrance, data.x);
	data.x_p = entrance->x;
	data.y_p = entrance->y;
	if (!is_valid(&data, entrance, data.n_col))
		handle_error(data.map, NULL, data.y, "Error\nInvalid map");
	start_game(&data);
}
