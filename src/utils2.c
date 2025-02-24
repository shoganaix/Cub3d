/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:33 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/24 17:06:20 by macastro         ###   ########.fr       */
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
		printf("INFO. angle:%f x_inc:%i y_inc:%i\n", angle, x_inc, y_inc); //
		my_perror_exit("assert_directions failed");
	}
}

/**
 * returns NULL if memory allocation fails.
 */
char	**copy_map_arr(t_map m)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)ft_calloc((m.height + 1), sizeof(char *));
	if (map_copy == NULL)
		return (NULL);
	i = 0;
	while (i < m.height)
	{
		map_copy[i] = ft_strdup(m.map[i]);
		if (map_copy[i] == NULL)
			return (ft_free_arrstr(map_copy), NULL);
		i++;
	}
	return (map_copy);
}