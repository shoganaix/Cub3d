/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:33 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/03 12:49:05 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	dist_pts(int a[2], int b[2])
{
	return (floor(sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2))));
}

int	grid_row(int point[2])
{
	return (point[Y] / CUB_SIZE);
}

int	grid_column(int point[2])
{
	return (point[X] / CUB_SIZE);
}

void	assign_point(int dst[2], int src[2])
{
	dst[X] = src[X];
	dst[Y] = src[Y];
}

void	assign_point_ints(int dst[2], int x, int y)
{
	dst[X] = x;
	dst[Y] = y;
}
