/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpittigl <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:28:46 by lpittigl          #+#    #+#             */
/*   Updated: 2024/09/16 15:28:49 by lpittigl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdarg.h>
# include "minilibx-linux/mlx.h"
# include "X11/keysym.h"

# ifndef GET_NEXT_LINE_H
#  define GET_NEXT_LINE_H

#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 100
#  endif

size_t	len(const char *s);
char	*ft_strjoin(char *s1, char *s2, int i, int j);
char	*ft_substr(char *s, size_t start, size_t len, int if_free);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		recover_mem(char **s, char **mem);
void	read_from_file(char **s, int fd, ssize_t i);
char	*get_next_line(int fd);

# endif

# ifndef FT_PRINTF_H
#  define FT_PRINTF_H

int		ft_printf(const char *s, ...);

# endif

# define RIGHT 1
# define LEFT -1
# define UP -2
# define DOWN 2
# define WALL '1'
# define COLL 'C'
# define PLAYER 'P'
# define GROUND '0'
# define EXIT 'E'
# define PLAY_OVER_EXIT 'F'
# define FRONT "textures/Goblin_Front.xpm"
# define GRASS "textures/grass.xpm"
# define WATER "textures/Water.xpm"
# define COLLE "textures/Collectibles.xpm"
# define OPEN "textures/exit_open.xpm"
# define CLOSED "textures/exit_close.xpm"
# define P_O_E "textures/Player_over_exit.xpm"
# define SIZE_OF_TILE 128
# define DISP_IMG mlx_put_image_to_window
# define N_GAME "Playing with fire"
# define NEW_WIN mlx_new_window

typedef struct t_list
{
	int				x;
	int				y;
	struct t_list	*next;
}	t_list;

typedef struct s_map
{
	char	**map;
	int		exit_flag;
	int		n_col;
	int		n_entr;
	int		n_exit;
	int		x_p;
	int		y_p;
	int		y;
	int		x;
	int		move_counter;
}				t_map;

typedef struct s_pictures
{
	void	*water;
	void	*grass;
	void	*player;
	void	*exit_o;
	void	*exit_c;
	void	*coll;
	void	*p_o_e;
}	t_pictures;

typedef struct s_utils
{
	void		*mlx;
	void		*win;
	t_map		*data;
	t_pictures	images;
}				t_utils;

t_list	*ft_lstnew(int column, int row);
char	*get_next_line(int fd);
int		ft_strlen(char *c);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_bzero(char *s, int n);
char	**zero_matrix(int n_lines, int width, t_map *data, t_list *c);
void	destroy_array(char **array, int y);
void	handle_error(char **map, t_list	*curr, int y, char *s);
int		is_valid(t_map *data, t_list *c, int n_col);
void	next_in_list(t_list **current);
int		start_game(t_map *data);
t_map	set_data(void);
int		close_window(t_utils *destroy);
void	close_program(t_utils *mlx, int signal);
void	destroy_images(t_utils *mlx);
void	check_which(t_utils *g, int keysim);
void	place_map(t_utils *gm, t_pictures img, int x, int y);
int		event_handler(int keysim, t_utils *mlx_utils);
void	check_file(char *file);

#endif