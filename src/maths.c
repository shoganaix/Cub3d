/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:17:28 by macastro          #+#    #+#             */
/*   Updated: 2025/02/21 20:02:03 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * degrees
 */
float	ft_tan(float degrees)
{
	float	rad;

	rad = degrees * M_PI / 180;
	return (tan(rad));
}

/**
 * degrees
 */
float	ft_sin(float degrees)
{
	float	rad;

	rad = degrees * M_PI / 180;
	return (sin(rad));
}

/**
 * degrees
 */
float	ft_cos(float degrees)
{
	float	rad;

	rad = degrees * M_PI / 180;
	return (cos(rad));
}
