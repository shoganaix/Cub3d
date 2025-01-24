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

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -g3 -O3 -c $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C mlx_linux
	make -C libft
	$(CC) $(OBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

$(NAMETEST): $(TESTOBJ)
	make -C mlx_linux
	make -C libft
	$(CC) $(TESTOBJ) -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAMETEST)

clean:
	rm -rfv $(OBJ)
	make clean -C mlx_linux
	make clean -C libft

fclean: clean
	rm -rfv $(NAME)
	rm -rfv $(NAMETEST)
	make fclean -C libft

re: fclean all

test: 		$(NAMETEST)

.PHONY: all clean fclean re test