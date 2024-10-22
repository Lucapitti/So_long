/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_error_handling.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:59:24 by lpittigl          #+#    #+#             */
/*   Updated: 2024/09/18 15:59:26 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_utils *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->images.coll);
	mlx_destroy_image(mlx->mlx, mlx->images.exit_c);
	mlx_destroy_image(mlx->mlx, mlx->images.exit_o);
	mlx_destroy_image(mlx->mlx, mlx->images.grass);
	mlx_destroy_image(mlx->mlx, mlx->images.player);
	mlx_destroy_image(mlx->mlx, mlx->images.p_o_e);
	mlx_destroy_image(mlx->mlx, mlx->images.water);
}

void	close_program(t_utils *mlx, int signal)
{
	if (signal == 0)
		ft_printf("Closing game.\n");
	if (signal == 3)
		ft_printf("Whoa! You did IT, congratulations!\n");
	destroy_images(mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	destroy_array(mlx->data->map, mlx->data->y);
	free(mlx->mlx);
	exit (0);
}

int	close_window(t_utils *destroy)
{
	event_handler(XK_Escape, destroy);
	return (0);
}

void	destroy_array(char **array, int y)
{
	while (y-- > 0)
	{
		free (array[y]);
	}
	free (array);
}

void	handle_error(char **map, t_list	*curr, int y, char *s)
{
	ft_printf("%s\n", s);
	if (map)
		destroy_array(map, y);
	if (curr)
		while (curr)
			next_in_list(&curr);
	exit (0);
}
