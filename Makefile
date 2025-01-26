# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 11:17:31 by msoriano          #+#    #+#              #
#    Updated: 2025/01/24 20:09:14 by macastro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAMETEST = testing

SRC = src/main.c \
		src/hooks.c \
		src/image.c \
		src/map.c \
		src/parse.c \
		src/window.c \
		src/error.c \
		src/info.c \
		src/debug.c
#src/playground.c

TESTSRC = test/test_map.c \
		src/hooks.c \
		src/image.c \
		src/map.c \
		src/parse.c \
		src/window.c \
		src/error.c \
		src/info.c \
		src/debug.c


OBJ = $(SRC:.c=.o)
TESTOBJ = $(TESTSRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

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


%.o: %.c
# $(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -g3 -O3 -c $< -o $@
	$(CC) $(CFLAGS) -c $< -o $@

$(NAMETEST): $(TESTOBJ)
	make -C $(MLX_PATH)
	make -C libft
#	$(CC) $(TESTOBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAMETEST)
	$(CC) $(TESTOBJ) $(LIBFT) $(MLX_LIB) -o $(NAMETEST)

clean:
	rm -rfv $(OBJ)
	make clean -C $(MLX_PATH)
	make clean -C libft

fclean: clean
	rm -rfv $(NAME)
	rm -rfv $(NAMETEST)
	make fclean -C libft

re: fclean all

test: 		$(NAMETEST)

.PHONY: all clean fclean re test