/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:12:17 by macastro          #+#    #+#             */
/*   Updated: 2025/02/12 17:02:50 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
