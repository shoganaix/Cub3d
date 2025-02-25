/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/25 17:25:50 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_img(t_game game, char *img_path, int posX, int posY)
{
	t_image	img;
	int		img_width;
	int		img_height;

	img.mlximg = mlx_xpm_file_to_image(game.mlx, img_path,
			&img_width, &img_height);
	mlx_put_image_to_window(game.mlx, game.win, img.mlximg, posX, posY);
	mlx_destroy_image(game.mlx, img.mlximg);
}

t_image	read_image(t_game *game, char *img_path)
{
	t_image	img;

	img.mlximg = mlx_xpm_file_to_image(game->mlx, img_path,
			&img.width, &img.height);
	return (img);
}

/**
 * BIG ENDIAN
 * color 0xrrggbb -> 0x..AARRGGBB
 * 
 * LIL ENDIAN
 * color 0xrrggbb -> 0xBBGGRRAA..
*/
void	img_set_pixel_color(t_image *img, int pixel, t_color color, int alpha)
{
	char	*pixel_in_buffer;
	int		new_alpha;
	int		vals;

	vals = img->bits_per_pixel / 8;
	if (alpha != 1)
		new_alpha = 200;
	else
		new_alpha = 1;

    // fprintf(stderr, "Pixel %i\n", pixel);
    //fprintf(stderr, "Pixel * vals %i\n", pixel *  vals);
    //fprintf(stderr, "img W*H %i\n", WIN_H * WIN_W); //2073600
	pixel_in_buffer = &img->addr[pixel * vals];
	if (img->endian == 1)
	{
		pixel_in_buffer[vals - 4] = new_alpha;
		pixel_in_buffer[vals - 3] = color.r;
		pixel_in_buffer[vals - 2] = color.g;
		pixel_in_buffer[vals - 1] = color.b;
	}
	else
	{
		pixel_in_buffer[0] = color.b;
		pixel_in_buffer[1] = color.g;
		pixel_in_buffer[2] = color.r;
		pixel_in_buffer[3] = new_alpha;
	}
}

void	draw_bg_on_img(t_color color_ceiling, t_color color_floor, t_image *img)
{
	int	i;
	int	j;
	int	pixel;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			pixel = i * WIN_W + j;
			if (i < WIN_H / 2)
				img_set_pixel_color(img, pixel, color_ceiling, 1);
			else
				img_set_pixel_color(img, pixel, color_floor, 1);
			j++;
		}
		i++;
	}
}

t_image	new_empty_img(void *mlx, int width_px, int height_px)
{
	t_image	img;
	int		bytes_per_px;

	img.mlximg = mlx_new_image(mlx, width_px, height_px);
	img.addr = mlx_get_data_addr(img.mlximg,
			&img.bits_per_pixel, &img.line_size, &img.endian);
	if (img.bits_per_pixel % 8 != 0)
		my_perror_exit("bit per pixel failed");
	bytes_per_px = img.bits_per_pixel / 8;
	// img.chpp = bytes_per_px;
	// img.mlx = mlx;
	img.height = height_px;
	img.width = width_px;
	return (img);
}
