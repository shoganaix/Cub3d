/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:17:28 by macastro          #+#    #+#             */
/*   Updated: 2025/02/21 14:29:31 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * degrees
 */
float	ft_tan(int degrees)
{
	float	rad;

	rad = degrees * M_PI / 180;
	return (tan(rad));
}

/**
 * degrees
 */
float	ft_sin(int degrees)
{
	float	rad;

	rad = degrees * M_PI / 180;
	return (sin(rad));
}

/**
 * degrees
 */
float	ft_cos(int degrees)
{
	float	rad;

	rad = degrees * M_PI / 180;
	return (cos(rad));
}
