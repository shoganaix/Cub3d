/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:59:52 by macastro          #+#    #+#             */
/*   Updated: 2025/02/27 16:35:07 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_wall_collision(int point[2], int offset_x, int offset_y,
	t_world *world)
{
	int	next_point[2];

	assign_point_ints(next_point, point[X] + offset_x, point[Y] + offset_y);
	return (pos_is_wall(next_point, world));
}

t_bool	too_near_wall(int point[2], t_world *world)
{
	const int	min_dist = CUB_SIZE / 2;
	int			grid_pos[2];
	int			cell_pos[2];

	grid_pos[R] = grid_row(point);
	grid_pos[C] = grid_column(point);
	cell_pos[X] = point[X] % CUB_SIZE;
	cell_pos[Y] = point[Y] % CUB_SIZE;
	if (cell_pos[X] < min_dist && check_wall_collision(point,
			-cell_pos[X] - 1, 0, world)) // left
		return (TRUE);
	if (CUB_SIZE - cell_pos[X] < min_dist && check_wall_collision(point,
			cell_pos[X] + 1, 0, world)) // right
		return (TRUE);
	if (cell_pos[Y] < min_dist && check_wall_collision(point, 0,
			-cell_pos[Y] - 1, world)) // up
		return (TRUE);
	if (CUB_SIZE - cell_pos[Y] < min_dist && check_wall_collision(point, 0,
			cell_pos[Y] + 1, world)) // down
		return (TRUE);
	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
}

// t_bool	too_near_wall(int point[2], t_world *world)
// {
// 	const int	min_dist = CUB_SIZE / 2;
// 	int			grid_pos[2];
// 	int			cell_pos[2];
// 	int			next_point[2];

// 	grid_pos[R] = grid_row(point);
// 	grid_pos[C] = grid_column(point);
// 	cell_pos[X] = point[X] % CUB_SIZE;
// 	cell_pos[Y] = point[Y] % CUB_SIZE;
// 	if (cell_pos[X] < min_dist) // left
// 	{
// 		assign_point_ints(next_point, point[X] - cell_pos[X] - 1, point[Y]);
// 		if (pos_is_wall(next_point, world))
// 			return (TRUE);
// 		return (FALSE);
// 	}
// 	if (CUB_SIZE - cell_pos[X] < min_dist) // right
// 	{
// 		assign_point_ints(next_point, point[X] + cell_pos[X] + 1, point[Y]);
// 		if (pos_is_wall(next_point, world))
// 			return (TRUE);
// 		return (FALSE);
// 	}
// 	if (cell_pos[Y] < min_dist) // up
// 	{
// 		assign_point_ints(next_point, point[X], point[Y] - cell_pos[Y] - 1);
// 		if (pos_is_wall(next_point, world))
// 			return (TRUE);
// 		return (FALSE);
// 	}
// 	if (CUB_SIZE - cell_pos[Y] < min_dist) // down
// 	{
// 		assign_point_ints(next_point, point[X], point[Y] + cell_pos[Y] + 1);
// 		if (pos_is_wall(next_point, world))
// 			return (TRUE);
// 		return (FALSE);
// 	}
// 	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
// }

t_bool	pos_is_wall(int point[2], t_world *world)
{
	int	grid_pos[2];

	grid_pos[R] = grid_row(point);
	grid_pos[C] = grid_column(point);
	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
}
