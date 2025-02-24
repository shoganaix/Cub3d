/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:33 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/24 18:17:41 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	dist_between_points(int a[2], int b[2])
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
