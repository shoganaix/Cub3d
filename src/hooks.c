/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/25 12:23:36 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, t_moves move)
{
	const float	angle_inc = TURN;

	if (move == LEFT)
		game->world.pl_angle = sum_degrees(game->world.pl_angle, angle_inc);
	if (move == RIGHT)
		game->world.pl_angle = sum_degrees(game->world.pl_angle, -angle_inc);
}

/**
 * 'step size' is now called 'step'
 * 'next_point' is now called 'next_p'
 * 'move_direction_angle' is now called 'dir_ag'
 */
void	move_player(t_game *game, t_moves move)
{
	const float	step = CUB_SIZE / 2.0;
	float		dir_ag;
	float		next_p[2];

	dir_ag = 0.0;
	if (move == FORW)
		dir_ag = game->world.pl_angle;
	else if (move == BACKW)
		dir_ag = sum_degrees(game->world.pl_angle, -180);
	else if (move == LEFT)
		dir_ag = sum_degrees(game->world.pl_angle, 90);
	else if (move == RIGHT)
		dir_ag = sum_degrees(game->world.pl_angle, -90);
	else
		my_perror_exit("Unexpected move");
	assign_point_floats(next_p, game->world.pl_point[X] + step
		* ft_cos(dir_ag), game->world.pl_point[Y] - step * ft_sin(dir_ag));
	if (too_near_wall(next_p, &game->world))
		return ;
	if (pos_is_wall(next_p, &game->world))
		return ;
	if (!is_inside_grid(game->world.map, grid_row(next_p),
			grid_column(next_p), game->world.map_height))
		return ;
	assign_point(game->world.pl_point, next_p);
}

int	key_press_hndlr(int keycode, void *param)
{
	t_game	*game;

	if (keycode != KEY_ESC
		&& keycode != KEY_A && keycode != KEY_W
		&& keycode != KEY_S && keycode != KEY_D
		&& keycode != KEY_LEFT && keycode != KEY_RIGHT)
		return (0);
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
