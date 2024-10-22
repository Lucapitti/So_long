NAME = so_long
MLXPATH = $(CURDIR)/minilibx-linux
MLXFLAGS = -L$(MLXPATH) -lmlx_Linux -lX11 -lXext
CFLAGS = -Wall -Wextra -Werror
SRCS = so_long_main.c so_long_flood_fill.c so_long_utils.c \
		so_long_closing.c so_long_game.c so_long_movement.c \
		get_next_line.c get_next_line_utils.c ft_printf.c
OBJ	= $(patsubst %.c, %.o, $(SRCS))
CC = gcc
RM = rm -f
INC = -I./

MLX_DIR		= ./minilibx-linux
MLX_LIB		= libmlx_Linux.a

$(NAME): $(MLX_LIB) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -L$(MLX_DIR) -lmlx_Linux $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

all: $(NAME)

clean:
	$(RM) ${OBJ}

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean fclean re
