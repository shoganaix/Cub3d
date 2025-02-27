/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/27 16:49:10 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_player(t_game *game, t_moves move)
{
	const int	angle_inc = FOV / 4;

	debug("ROTATE");
	if (move == LEFT)
		game->world.pl_angle += angle_inc;
	if (move == RIGHT)
		game->world.pl_angle -= angle_inc;
	if (game->world.pl_angle > 360)
		game->world.pl_angle -= 360;
	if (game->world.pl_angle < 0)
		game->world.pl_angle += 360;
	debug("ROTATE DONE ✅"); //
}

void	move_player(t_game *game, t_moves move)
{
	const int	step_size = CUB_SIZE / 2;
	int			next_point[2];

	assign_point(next_point, game->world.pl_point);
	if (move == LEFT)
		next_point[X] -= step_size;
	if (move == RIGHT)
		next_point[X] += step_size;
	if (move == UP)
		next_point[Y] -= step_size;
	if (move == DOWN)
		next_point[Y] += step_size;
	if (!is_inside_grid(game->world.map, grid_row(next_point),
			grid_column(next_point), game->world.map_height)
		|| pos_is_wall(next_point, &game->world)
		|| too_near_wall(next_point, &game->world))
	{
		debug("MOVE ❌"); //
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
		move_player(game, DOWN);
	if (keycode == KEY_W)
		move_player(game, UP);
	if (keycode == KEY_D)
		move_player(game, RIGHT);
	if (keycode == KEY_LEFT)
		rotate_player(game, LEFT);
	if (keycode == KEY_RIGHT)
		rotate_player(game, RIGHT);
	draw_game(game);
	return (0);
}
