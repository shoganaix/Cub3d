/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:17 by macastro          #+#    #+#             */
/*   Updated: 2025/02/25 12:45:01 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_info(t_info *info)
{
	ft_bzero(info, sizeof(t_info));
	info->ceiling.r = -1;
	info->ceiling.g = -1;
	info->ceiling.b = -1;
	info->floor.r = -1;
	info->floor.g = -1;
	info->floor.b = -1;
}

void	destroy_info(t_info *info)
{
	int	i;

	i = 0;
	while (i < NUM_CARD)
	{
		if (info->tx_paths[i])
		{
			free(info->tx_paths[i]);
			info->tx_paths[i] = NULL;
		}
		++i;
	}
}

void	show_info(t_info info)
{
	int	i;

	i = 0;
	while (i < NUM_CARD)
	{
		if (info.tx_paths[i])
			ft_printf("\t%i texture: %s\n", i, info.tx_paths[i]);
		else
			ft_printf("\t%i texture: NULL\n", i);
		i++;
	}
	ft_printf("\tceiling %i %i %i\n",
		info.ceiling.r, info.ceiling.g, info.ceiling.b);
	ft_printf("\tfloor %i %i %i\n", info.floor.r, info.floor.g, info.floor.b);
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
