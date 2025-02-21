/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:59:52 by macastro          #+#    #+#             */
/*   Updated: 2025/02/21 15:19:27 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	pos_is_wall(int point[2], t_world *world)
{
	int	grid_pos[2];

	grid_pos[R] = grid_row(point);
	grid_pos[C] = grid_column(point);
	ft_printf("wall? point x:%i y:%i\n", point[X], point[Y]);
	ft_printf("wall? grid r:%i c:%i\n", grid_pos[R], grid_pos[C]);
	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
}
void	ray_collides_wall_vert(t_world *world, int angle, int col_point[2])
{
	int		a[2];
	int		y_inc;
	int		x_inc;
	int i = 0;

	debug("v----------------");

	y_inc = CUB_SIZE * ft_tan(angle);
	if (90 < angle && angle < 270)
	{
		a[0] = floor(world->pl_point[0] / CUB_SIZE) * CUB_SIZE - 1;
		x_inc = -1 * CUB_SIZE;
	}
	else
	{
		a[0] = floor(world->pl_point[0] / CUB_SIZE) * CUB_SIZE + 64;
		x_inc = CUB_SIZE;
	}
	a[1] = world->pl_point[1] + (world->pl_point[0] - a[0]) * ft_tan(angle);
	while (TRUE && i < 10)
	{
		debug_int("----vert", i++);
		if (pos_is_wall(a, world))
			break ;
		a[0] += x_inc;
		a[1] += y_inc;
	}
	col_point[0] = a[0];
	col_point[1] = a[1];
}

void	ray_collides_wall_hori(t_world *world, int angle, int col_point[2])
{
	int		p[2];
	int		y_inc;
	int		x_inc;
	int		i = 0;

	debug("h--------------");

	if (0 < angle && angle < 180)
	{
		p[Y] = grid_row(world->pl_point) * CUB_SIZE - 1;
		// x=96, a1 = 1 * 64 - 1 = 63 -> 0
		y_inc = -1 * CUB_SIZE;
	}
	else
	{
		p[Y] = grid_row(world->pl_point) * CUB_SIZE + CUB_SIZE;
		y_inc = CUB_SIZE;
	}
	p[X] = world->pl_point[X] + (world->pl_point[Y] - p[Y]) / ft_tan(angle);
	x_inc = CUB_SIZE / ft_tan(angle);
	
	while (TRUE && i < 10)
	{
		debug_int("----hori", i++);
		if (pos_is_wall(p, world))
			break ;
		p[0] += x_inc;
		p[1] += y_inc;
	}
	assign_point(col_point, p);
}

int	dist_between_points(int a[2], int b[2])
{
	return (floor(sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2))));
}

void	get_ray_collides_wall(t_world *world, int angle, int coll_point[2])
{
	int	vert_collision[2];
	int	hori_collision[2];
	int	dh;
	int	dv;

	dh = INT_MAX;
	dv = INT_MAX;
	if (angle != 0 && angle != 180)
	{
		ray_collides_wall_hori(world, angle, hori_collision);
		dh = dist_between_points(world->pl_point, hori_collision);
	}
	if (angle != 90 && angle != 270)
	{
		ray_collides_wall_vert(world, angle, vert_collision);
		dv = dist_between_points(world->pl_point, vert_collision);
	}
	if (dh <= dv)
		assign_point(coll_point, hori_collision);
	else
		assign_point(coll_point, vert_collision);
}
