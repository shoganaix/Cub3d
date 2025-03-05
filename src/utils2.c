/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:23:33 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/05 12:58:10 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * assert - optional
 */
void	assert_directions(float angle, float x_inc, float y_inc)
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
		my_perror_exit("assert_directions failed");
}

float	sum_degrees(float deg1, float deg2)
{
	deg1 += deg2;
	if (deg1 > 360)
		deg1 -= 360;
	if (deg1 < 0)
		deg1 += 360;
	return (deg1);
}
