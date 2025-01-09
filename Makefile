# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/03 11:17:31 by msoriano          #+#    #+#              #
#    Updated: 2025/01/09 18:46:25 by macastro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = src/main.c \
		src/hooks.c \
		src/image.c \
		src/map.c \
		src/parse.c \
		src/window.c \
		src/debug.c
#src/playground.c

OBJ = $(SRC:.c=.o)

CC = cc

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -g3 -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C mlx_linux
	make -C libft
	$(CC) $(OBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rfv $(OBJ)
	make clean -C mlx_linux
	make clean -C libft

fclean: clean
	rm -rfv $(NAME)
	make fclean -C libft

re: fclean all

test: 		$(NAME)
			./$(NAME) img/teapot.xpm

.PHONY: all clean fclean re