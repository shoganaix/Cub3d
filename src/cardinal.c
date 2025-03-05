/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cardinal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:17 by macastro          #+#    #+#             */
/*   Updated: 2025/03/05 12:41:28 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*cardinal_to_str(t_card c)
{
	if (c == NO)
		return ("NO");
	if (c == SO)
		return ("SO");
	if (c == WE)
		return ("WE");
	if (c == EA)
		return ("EA");
	my_perror_exit("Unexpected cardinal 1");
	return (NULL);
}

int	cardinal_to_angle(t_card c)
{
	if (c == EA)
		return (0);
	if (c == NO)
		return (90);
	if (c == WE)
		return (180);
	if (c == SO)
		return (270);
	my_perror_exit("Unexpected cardinal 2");
	return (-1);
}

t_card	char_to_cardinal(char c)
{
	if (c == 'N')
		return (NO);
	if (c == 'S')
		return (SO);
	if (c == 'W')
		return (WE);
	if (c == 'E')
		return (EA);
	my_perror_exit("Unexpected cardinal 3");
	return (-1);
}

t_card	get_cardinal_hori(float col_point[2])
{
	if ((int)col_point[Y] % CUB_SIZE == 0)
		return (NO);
	if ((int)col_point[Y] % CUB_SIZE == CUB_SIZE - 1)
		return (SO);
	return (0);
}


t_card	get_cardinal_veri(float col_point[2])
{
	if ((int)col_point[X] % CUB_SIZE == 0)
		return (WE);
	if ((int)col_point[X] % CUB_SIZE == CUB_SIZE - 1)
		return (EA);
	return (0);
}