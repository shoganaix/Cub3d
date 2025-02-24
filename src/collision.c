/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:59:52 by macastro          #+#    #+#             */
/*   Updated: 2025/02/24 18:02:27 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	pos_is_wall(int point[2], t_world *world)
{
	int	grid_pos[2];

	grid_pos[R] = grid_row(point);
	grid_pos[C] = grid_column(point);
	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
}

t_bool	ray_wall_loop(int p[2], int inc[2], t_world *world, int col_point[2])
{
	while (is_inside_grid(world->map, grid_row(p), grid_column(p),
			world->map_height))
	{
		if (pos_is_wall(p, world))
			return (assign_point(col_point, p), TRUE);
		assign_point_ints(p, p[X] + inc[X], p[Y] + inc[Y]);
	}
	return (FALSE);
}

t_bool	ray_collides_wall_vert(t_world *world, float angle, int col_point[2])
{
	int		p[2];
	int		inc[2];

	if (angle == 90 || angle == 270)
		return (FALSE);
	inc[X] = CUB_SIZE;
	inc[Y] = CUB_SIZE * ft_tan(angle);
	if (90 < angle && angle < 270)
	{
		p[X] = grid_column(world->pl_point) * CUB_SIZE - 1;
		inc[X] *= -1;
	}
	else
	{
		p[X] = grid_column(world->pl_point) * CUB_SIZE + CUB_SIZE;
		inc[Y] *= -1;
	}
	p[Y] = world->pl_point[Y] + (world->pl_point[X] - p[X]) * ft_tan(angle);
	assert_directions(angle, inc[X], inc[Y]);
	return (ray_wall_loop(p, inc, world, col_point));
}

t_bool	ray_collides_wall_hori(t_world *world, float angle, int col_point[2])
{
	int		p[2];
	int		inc[2];

	if (angle == 0 || angle == 180)
		return (FALSE);
	inc[X] = CUB_SIZE / ft_tan(angle);
	inc[Y] = CUB_SIZE;
	if (0 < angle && angle < 180)
	{
		p[Y] = grid_row(world->pl_point) * CUB_SIZE - 1;
		inc[Y] *= -1;
	}
	else
	{
		p[Y] = grid_row(world->pl_point) * CUB_SIZE + CUB_SIZE;
		inc[X] *= -1;
	}
	p[X] = world->pl_point[X] + (world->pl_point[Y] - p[Y]) / ft_tan(angle);
	assert_directions(angle, inc[X], inc[Y]);
	return (ray_wall_loop(p, inc, world, col_point));
}

void	get_ray_collides_wall(t_world *world, float angle, int coll_point[2])
{
	int	vert_collision[2];
	int	hori_collision[2];
	int	dh;
	int	dv;

	dh = INT_MAX;
	dv = INT_MAX;
	if (ray_collides_wall_hori(world, angle, hori_collision))
		dh = dist_between_points(world->pl_point, hori_collision);
	if (ray_collides_wall_vert(world, angle, vert_collision))
		dv = dist_between_points(world->pl_point, vert_collision);
	if (dh <= dv)
		assign_point(coll_point, hori_collision);
	else
		assign_point(coll_point, vert_collision);
}
