/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:17 by macastro          #+#    #+#             */
/*   Updated: 2025/02/03 13:06:27 by msoriano         ###   ########.fr       */
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
		if (info->textures[i])
		{
			free(info->textures[i]);
			info->textures[i] = NULL;
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
		if (info.textures[i])
			printf("\t%i texture: %s\n", i, info.textures[i]);
		else
			printf("\t%i texture: NULL\n", i);
		i++;
	}
	printf("\tceiling %i %i %i\n",
		info.ceiling.r, info.ceiling.g, info.ceiling.b);
	printf("\tfloor %i %i %i\n", info.floor.r, info.floor.g, info.floor.b);
}

char	*cardinal_tostr(t_card c)
{
	if (c == NO)
		return ("NO");
	if (c == SO)
		return ("SO");
	if (c == WE)
		return ("WE");
	if (c == EA)
		return ("EA");
	my_perror_exit("Unexpected cardinal");
	return (NULL);
}
