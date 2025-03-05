/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:34:09 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/05 12:42:30 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool	ray_wall_loop(float p[2], float inc[2], t_world *world, float col_point[2])
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

t_bool	ray_collides_wall_vert(t_world *world, float angle, float col_point[2])
{
	float		p[2];
	float	inc[2];

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

t_bool	ray_collides_wall_hori(t_world *world, float angle, float col_point[2])
{
	float		p[2];
	float	inc[2];

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

/**
 * get ray-wall collision point
 * Needs:
 * - world (context, player)
 * - ray angle in degrees
 * returns
 * - collision point in argument coll_point
 * - collision wall cardinal (NSEW) in argument coll_card
 */
void	get_ray_wall_coll_pt(t_world *world, float ray, float coll_point[2],
	t_card *coll_card)
{
	float		vert_collision[2];
	float		hori_collision[2];
	float	dh;
	float	dv;

	ft_bzero(coll_point, 2 * sizeof(int));
	dh = 1.0 * INT_MAX;
	dv = 1.0 * INT_MAX;
	if (ray_collides_wall_hori(world, ray, hori_collision))
		dh = dist_pts(world->pl_point, hori_collision);
	if (ray_collides_wall_vert(world, ray, vert_collision))
		dv = dist_pts(world->pl_point, vert_collision);
	if (dh <= dv)
	{
		assign_point(coll_point, hori_collision);
		*coll_card = get_cardinal_hori(coll_point);
	}
	else
	{
		assign_point(coll_point, vert_collision);
		*coll_card = get_cardinal_veri(coll_point);
	}
	//debug_int("wall", *coll_card);
}
