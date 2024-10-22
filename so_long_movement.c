/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_movement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:10:44 by lpittigl          #+#    #+#             */
/*   Updated: 2024/09/18 16:10:48 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_map2(t_utils *g, int dx, int dy)
{
	if (g->data->map[g->data->y_p + dy][g->data->x_p + dx] == COLL)
		g->data->n_col--;
	if (g->data->map[g->data->y_p + dy][g->data->x_p + dx] == EXIT
		&& g->data->n_col != 0)
		g->data->map[g->data->y_p + dy][g->data->x_p + dx] = PLAY_OVER_EXIT;
	else if (g->data->map[g->data->y_p + dy][g->data->x_p + dx] == EXIT
		&& g->data->n_col == 0)
		close_program(g, 3);
	else
		g->data->map[g->data->y_p + dy][g->data->x_p + dx] = PLAYER;
	g->data->x_p += dx;
	g->data->y_p += dy;
}

void	update_map(t_utils *game, int which)
{
	if (game->data->map[game->data->y_p][game->data->x_p] == PLAY_OVER_EXIT)
		game->data->map[game->data->y_p][game->data->x_p] = 'E';
	else
		game->data->map[game->data->y_p][game->data->x_p] = '0';
	if (which == LEFT || which == RIGHT)
		update_map2(game, which, 0);
	else if (which == UP || which == DOWN)
		update_map2(game, 0, (which / 2));
	ft_printf("You have moved %d times\n", ++game->data->move_counter);
}

void	check_which(t_utils *g, int keysim)
{
	if (keysim == XK_w && g->data->map[g->data->y_p - 1][g->data->x_p] != WALL)
		update_map(g, UP);
	if (keysim == XK_s && g->data->map[g->data->y_p + 1][g->data->x_p] != WALL)
		update_map(g, DOWN);
	if (keysim == XK_a && g->data->map[g->data->y_p][g->data->x_p - 1] != WALL)
		update_map(g, LEFT);
	if (keysim == XK_d && g->data->map[g->data->y_p][g->data->x_p + 1] != WALL)
		update_map(g, RIGHT);
	place_map(g, g->images, 0, 0);
}
