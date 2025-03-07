/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:59:52 by macastro          #+#    #+#             */
/*   Updated: 2025/03/06 16:33:49 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	check_wall_collision(float point[2], float offset_x, float offset_y,
	t_world *world)
{
	float	next_point[2];

	assign_point_floats(next_point, point[X] + offset_x, point[Y] + offset_y);
	return (pos_is_wall(next_point, world));
}

t_bool	too_near_wall(float point[2], t_world *world)
{
	const float	min_dist = CUB_SIZE / 4.0;
	int			grid_pos[2];
	float		cell_pt[2];

	grid_pos[R] = grid_row(point);
	grid_pos[C] = grid_column(point);
	cell_pt[X] = (int)point[X] % CUB_SIZE;
	cell_pt[Y] = (int)point[Y] % CUB_SIZE;
	if (cell_pt[X] < min_dist && check_wall_collision(point,
			-cell_pt[X] - 1, 0, world))
		return (TRUE);
	if (CUB_SIZE - cell_pt[X] < min_dist && check_wall_collision(point,
			cell_pt[X] + 1, 0, world))
		return (TRUE);
	if (cell_pt[Y] < min_dist && check_wall_collision(point, 0,
			-cell_pt[Y] - 1, world))
		return (TRUE);
	if (CUB_SIZE - cell_pt[Y] < min_dist && check_wall_collision(point, 0,
			cell_pt[Y] + 1, world))
		return (TRUE);
	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
}

t_bool	pos_is_wall(float point[2], t_world *world)
{
	int	grid_pos[2];

	grid_pos[R] = grid_row(point);
	grid_pos[C] = grid_column(point);
	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
}
