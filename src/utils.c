/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:33 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/05 12:39:44 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dist_pts(float a[2], float b[2])
{
	return (floor(sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2))));
}

int	grid_row(float point[2])
{
	return (point[Y] / CUB_SIZE);
}

int	grid_column(float point[2])
{
	return (point[X] / CUB_SIZE);
}

void	assign_point(float dst[2], float src[2])
{
	dst[X] = src[X];
	dst[Y] = src[Y];
}

void	assign_point_ints(float dst[2], float x, float y)
{
	dst[X] = x;
	dst[Y] = y;
}
