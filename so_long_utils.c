/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:58:24 by lpittigl          #+#    #+#             */
/*   Updated: 2024/09/18 15:58:26 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_file(char *file)
{
	int	lenght;
	int	i;

	i = 0;
	lenght = ft_strlen(file);
	while (i < lenght - 4)
		if (file[i++] == '.')
			handle_error(NULL, NULL, 0, "Error\nInvalid map format");
	if (lenght >= 4)
	{
		if (file[lenght - 4] == '.' && file[lenght - 3] == 'b'
			&& file[lenght - 2] == 'e' && file[lenght - 1] == 'r')
			return ;
	}
	handle_error(NULL, NULL, 0, "Error\nInvalid map format");
}

t_map	set_data(void)
{
	t_map	data;

	data.n_col = 0;
	data.n_entr = 0;
	data.y = 0;
	data.n_exit = 0;
	data.exit_flag = 0;
	data.move_counter = 0;
	return (data);
}

void	ft_bzero(char *s, int n)
{
	char	*temp;
	int		count;

	temp = s;
	count = 0;
	while (count < n)
	{
		temp[count] = '0';
		count++;
	}
	temp[count] = 0;
}

int	ft_strlen(char *s)
{
	int	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

t_list	*ft_lstnew(int x, int y)
{
	t_list	*head;

	head = (t_list *)malloc(sizeof(t_list));
	if (head)
	{
		head->x = x;
		head->y = y;
		head->next = NULL;
	}
	return (head);
}
