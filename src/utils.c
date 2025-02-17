/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:17 by macastro          #+#    #+#             */
/*   Updated: 2025/02/17 22:38:10 by msoriano         ###   ########.fr       */
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

t_card	chartocard(char c)
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
