# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 11:17:31 by msoriano          #+#    #+#              #
#    Updated: 2025/02/24 11:24:22 by msoriano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_T = testing

CC = cc
CFLAGS = -Wall -Wextra -Werror

# common
SRCFILES = src/hooks.c \
		src/image.c \
		src/map.c \
		src/cubfile.c \
		src/parse.c \
		src/window.c \
		src/error.c \
		src/error2.c \
		src/info.c \
		src/info2.c \
		src/utils.c \
		src/utils2.c \
		src/game.c \
		src/maths.c \
		src/collision.c \
		src/debug.c

TEST_SRC = test/test_map.c 

SRC =  src/main.c $(SRCFILES)
#src/playground.c
SRC_T = $(TEST_SRC) $(SRCFILES)

OBJ = $(SRC:%.c=build/%.o)
OBJ_T = $(SRC_T:%.c=build/%.o)

LIBFT = -Llibft -lft # Lib path, lib link
# LIBFT	= $(LIBFT_PATH)/libft.a

MLX_LOCAL = -Lmlx_linux -lmlx_Linux -Imlx_linux
L_GLOBAL = -L/usr/lib
L_X11 = -lXext -lX11
L_OTHERS = -lm -lz # math and zip
MLX_LINUX = $(MLX_LOCAL) $(L_GLOBAL) $(L_X11) $(L_OTHERS)

MLX_LOCAL2 = -Imlx -Lmlx_macos -lmlx
OPENGL = -framework OpenGL -framework AppKit
MLX_MACOS = $(MLX_LOCAL2) $(OPENGL)

UNAME = $(shell uname)
MLX_LIB	= $(MLX_LINUX)
MLX_PATH = mlx_linux
ifeq ($(UNAME),Darwin)
	MLX_LIB = $(MLX_MACOS)
	MLX_PATH = mlx_macos
endif


all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_PATH)
	make -C libft
#	$(CC) $(OBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
#	$(CC) $(OBJ) $(LIBFT) $(MLX_LINUX) -o $(NAME)
	$(CC) $(OBJ) $(LIBFT) $(MLX_LIB) -o $(NAME)


build/%.o: %.c
	@mkdir -p $(dir $@)
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -g3 -O3 -c $< -o $@
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_T): $(OBJ_T)
	make -C $(MLX_PATH)
	make -C libft
#	$(CC) $(OBJ_T) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME_T)
	$(CC) $(OBJ_T) $(LIBFT) $(MLX_LIB) -o $(NAME_T)

clean:
	rm -rfv build
	make clean -C $(MLX_PATH)
	make clean -C libft

fclean: clean
	rm -rfv $(NAME)
	rm -rfv $(NAME_T)
	make fclean -C libft

re: fclean all

test: 		$(NAME_T)

.PHONY: all clean fclean re test