/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 15:12:08 by msoriano         ###   ########.fr       */
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
