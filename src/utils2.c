/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:33 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/24 11:32:59 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
