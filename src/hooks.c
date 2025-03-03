/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/03 11:55:34 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, t_moves move)
{
	const int	angle_inc = FOV / 4;

	if (move == LEFT)
		game->world.pl_angle = sum_degrees(game->world.pl_angle, angle_inc);
	if (move == RIGHT)
		game->world.pl_angle = sum_degrees(game->world.pl_angle, -angle_inc);

	printf("new angle %f\n", game->world.pl_angle); //
	debug("ROTATE 🔄"); //
}

void	move_player(t_game *game, t_moves move)
{
	const int	step_size = CUB_SIZE / 2;
	float		move_dir_angle;
	int			next_point[2];

	move_dir_angle = 0.0;
	if (move == FORW)
		move_dir_angle = game->world.pl_angle;
	else if (move == BACKW)
		move_dir_angle = sum_degrees(game->world.pl_angle, -180);
	else if (move == LEFT)
		move_dir_angle = sum_degrees(game->world.pl_angle, 90);
	else if (move == RIGHT)
		move_dir_angle = sum_degrees(game->world.pl_angle, -90);
	else
		my_perror_exit("Unexpected move");
	assign_point_ints(next_point,
		game->world.pl_point[X] + step_size * ft_cos(move_dir_angle),
		game->world.pl_point[Y] - step_size * ft_sin(move_dir_angle));
	printf("MOVE next: (x, y) = (%i, %i)\n", next_point[X], next_point[Y]); //
	printf("MOVE next: cell(x, y) = (%i, %i)\n", next_point[X]%CUB_SIZE, next_point[Y]%CUB_SIZE);
	if (too_near_wall(next_point, &game->world))
	{
		debug("MOVE ❌ too near wall"); //
		return ;
	}
	if (pos_is_wall(next_point, &game->world))
	{
		debug("MOVE ❌ wall"); //
		return ;
	}
	if (!is_inside_grid(game->world.map, grid_row(next_point),
			grid_column(next_point), game->world.map_height))
	{
		debug("MOVE ❌ out of grid"); //
		return ;
	}
	debug("MOVE ✅"); //
	assign_point(game->world.pl_point, next_point);
}

int	key_press_hndlr(int keycode, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_A)
		move_player(game, LEFT);
	if (keycode == KEY_S)
		move_player(game, BACKW);
	if (keycode == KEY_W)
		move_player(game, FORW);
	if (keycode == KEY_D)
		move_player(game, RIGHT);
	if (keycode == KEY_LEFT)
		rotate_player(game, LEFT);
	if (keycode == KEY_RIGHT)
		rotate_player(game, RIGHT);
	draw_game(game);
	return (0);
}
