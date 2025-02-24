/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 18:06:01 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/24 18:37:38 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color	assign_color(t_image img,
		char *pixel_in_buffer, int vals)
{
	t_color	color;

	if (img.endian == 1)
	{
		//alpha = pixel_in_buffer[vals - 4];
		color.r = pixel_in_buffer[vals - 3];
		color.g = pixel_in_buffer[vals - 2];
		color.b = pixel_in_buffer[vals - 1];
	}
	else
	{
		color.b = pixel_in_buffer[0];
		color.g = pixel_in_buffer[1];
		color.r = pixel_in_buffer[2];
		// alpha = pixel_in_buffer[3];
	}
	return (color);
}

t_color	read_pixel_from_image(t_image img, int offset, int cube_height)
{
	int		tx_height;
	int		pixel;
	int		vals;
	char	*pixel_in_buffer;

	tx_height = cube_height * img.height / CUB_SIZE;
	img.addr = mlx_get_data_addr(img.mlximg,
			&img.bits_per_pixel, &img.line_size, &img.endian);
	if (img.bits_per_pixel % 8 != 0)
		my_perror_exit("bit per pixel failed");
	vals = img.bits_per_pixel / 8;
	pixel = tx_height * img.height + offset;
	pixel_in_buffer = &img.addr[pixel * vals];
	return (assign_color(img, pixel_in_buffer, vals));
}
