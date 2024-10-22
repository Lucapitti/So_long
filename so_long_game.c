/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:56:06 by lpittigl          #+#    #+#             */
/*   Updated: 2024/09/18 13:56:09 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	retrive_pict_pointer(t_pictures *images, t_utils data)
{
	int	size;

	size = SIZE_OF_TILE;
	images->water = mlx_xpm_file_to_image(data.mlx, WATER, &size, &size);
	images->coll = mlx_xpm_file_to_image(data.mlx, COLLE, &size, &size);
	images->exit_c = mlx_xpm_file_to_image(data.mlx, CLOSED, &size, &size);
	images->exit_o = mlx_xpm_file_to_image(data.mlx, OPEN, &size, &size);
	images->player = mlx_xpm_file_to_image(data.mlx, FRONT, &size, &size);
	images->grass = mlx_xpm_file_to_image(data.mlx, GRASS, &size, &size);
	images->p_o_e = mlx_xpm_file_to_image(data.mlx, P_O_E, &size, &size);
}

void	place_map(t_utils *gm, t_pictures img, int x, int y)
{
	while (y < gm->data->y)
	{
		x = 0;
		while (gm->data->map[y][x])
		{
			if (gm->data->map[y][x] == GROUND)
				DISP_IMG(gm->mlx, gm->win, img.grass, (x * 128), (y * 128));
			if (gm->data->map[y][x] == WALL)
				DISP_IMG(gm->mlx, gm->win, img.water, (x * 128), (y * 128));
			if (gm->data->map[y][x] == PLAYER)
				DISP_IMG(gm->mlx, gm->win, img.player, (x * 128), (y * 128));
			if (gm->data->map[y][x] == EXIT && gm->data->n_col != 0)
				DISP_IMG(gm->mlx, gm->win, img.exit_c, (x * 128), (y * 128));
			else if (gm->data->map[y][x] == EXIT && gm->data->n_col == 0)
				DISP_IMG(gm->mlx, gm->win, img.exit_o, (x * 128), (y * 128));
			if (gm->data->map[y][x] == PLAY_OVER_EXIT)
				DISP_IMG(gm->mlx, gm->win, img.p_o_e, (x * 128), (y * 128));
			if (gm->data->map[y][x] == COLL)
				DISP_IMG(gm->mlx, gm->win, img.coll, (x * 128), (y * 128));
			x++;
		}
		y++;
	}
}

int	event_handler(int keysim, t_utils *mlx_utils)
{
	if (keysim == XK_Escape)
		close_program(mlx_utils, 0);
	if (keysim == XK_d || keysim == XK_w || keysim == XK_a || keysim == XK_s)
		check_which(mlx_utils, keysim);
	return (0);
}

int	start_game(t_map *data)
{
	t_utils		info;

	info.mlx = mlx_init();
	info.win = NEW_WIN(info.mlx, (128 * data->x), (128 * data->y), N_GAME);
	info.data = data;
	retrive_pict_pointer(&info.images, info);
	place_map(&info, info.images, 0, 0);
	mlx_key_hook(info.win, event_handler, &info);
	mlx_hook(info.win, 17, 0, close_window, &info);
	mlx_loop(info.mlx);
	return (0);
}
