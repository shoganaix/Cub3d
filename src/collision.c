/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:59:52 by macastro          #+#    #+#             */
/*   Updated: 2025/02/21 20:20:01 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * assert - optional
 */
void	assert_directions(float angle, int x_inc, int y_inc)
{
	t_bool	err;

	err = FALSE;
	if ((angle == 0 && !(x_inc >= 0))
		|| (angle == 90 && !(y_inc <= 0))
		|| (angle == 180 && !(x_inc <= 0))
		|| (angle == 270 && !(y_inc >= 0))
		|| (0 < angle && angle < 90 && !(x_inc >= 0 && y_inc <= 0))
		|| (90 < angle && angle < 180 && !(x_inc <= 0 && y_inc <= 0))
		|| (180 < angle && angle < 270 && !(x_inc <= 0 && y_inc >= 0))
		|| (270 < angle && angle < 360 && !(x_inc >= 0 && y_inc >= 0)))
		err = TRUE;
	if (err)
	{
		printf("INFO. angle:%f x_inc:%i y_inc:%i\n", angle, x_inc, y_inc);
		my_perror_exit("assert_directions failed");
	}
}

t_bool	pos_is_wall(int point[2], t_world *world)
{
	int	grid_pos[2];

	grid_pos[R] = grid_row(point);
	grid_pos[C] = grid_column(point);
	//ft_printf("wall? point x:%i y:%i\n", point[X], point[Y]);
	//ft_printf("wall? grid r:%i c:%i\n", grid_pos[R], grid_pos[C]);
	return (world->map[grid_pos[R]][grid_pos[C]] == '1');
}

t_bool	ray_collides_wall_vert(t_world *world, float angle, int col_point[2])
{
	int		p[2];
	int		y_inc;
	int		x_inc;

	debug("v----------------"); //
	if (angle == 90 || angle == 270)
		return (FALSE);
	x_inc = CUB_SIZE;
	y_inc = CUB_SIZE * ft_tan(angle);
	if (90 < angle && angle < 270)
	{
		p[X] = grid_column(world->pl_point) * CUB_SIZE - 1;
		x_inc *= -1;
	}
	else
	{
		p[X] = grid_column(world->pl_point) * CUB_SIZE + CUB_SIZE;
		y_inc *= -1;
	}
	p[Y] = world->pl_point[Y] + (world->pl_point[X] - p[X]) * ft_tan(angle);
	assert_directions(angle, x_inc, y_inc);
	while (is_inside_grid(world->map, grid_row(p), grid_column(p),
			world->map_height))
	{
		if (pos_is_wall(p, world))
			return (assign_point(col_point, p), TRUE);
		assign_point_ints(p, p[X] + x_inc, p[Y] + y_inc);
	}
	return (FALSE);
}

t_bool	ray_collides_wall_hori(t_world *world, float angle, int col_point[2])
{
	int		p[2];
	int		y_inc;
	int		x_inc;

	debug("h--------------"); //
	if (angle == 0 || angle == 180)
		return (FALSE);
	x_inc = CUB_SIZE / ft_tan(angle);
	y_inc = CUB_SIZE;
	if (0 < angle && angle < 180)
	{
		p[Y] = grid_row(world->pl_point) * CUB_SIZE - 1;
		y_inc *= -1;
	}
	else
	{
		p[Y] = grid_row(world->pl_point) * CUB_SIZE + CUB_SIZE;
		x_inc *= -1;
	}
	p[X] = world->pl_point[X] + (world->pl_point[Y] - p[Y]) / ft_tan(angle);
	assert_directions(angle, x_inc, y_inc);
	while (is_inside_grid(world->map, grid_row(p), grid_column(p),
			world->map_height))
	{
		//debug("----hori"); // 
		if (pos_is_wall(p, world))
			return (assign_point(col_point, p), TRUE);
		assign_point_ints(p, p[X] + x_inc, p[Y] + y_inc);
	}
	return (FALSE);
}

int	dist_between_points(int a[2], int b[2])
{
	return (floor(sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2))));
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
