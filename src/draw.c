/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:54:43 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/24 18:44:30 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * TO DO:
 * El problema esta en que no entra en el bucle porque nuestro
 * 	p_wall[0][Y] (la i) > p_wall[1][Y]
 */
void	draw_slice(t_game *game, int p_wall[2][2], int offset)
{
	int		i;
	int		pixel_to_paint;
	t_color	color;

	i = p_wall[0][Y];
	printf("Nuestra altura es: %d\n", p_wall[1][Y]); //
	printf("Nuestra i es: %d\n", p_wall[0][Y]); //
	printf("Entra en el Bucle si: %d\n", i < p_wall[1][Y]); //
	while (i < p_wall[1][Y])
	{
		pixel_to_paint = i * WIN_W + p_wall[0][X];
		color = read_pixel_from_image(game->img, offset, i);
		printf("Color: R=%d, G=%d, B=%d\n", color.r, color.g, color.b); //
		img_set_pixel_color(&game->img, pixel_to_paint, color);
		i++;
	}
}

void	draw_game_on_img(t_game *game)
{
	float		angle;
	int			i;
	int			ray_collides_wall[2];
	int			p_wall[2][2];

	ft_bzero(&ray_collides_wall, sizeof(int) * 2);
	angle = game->world.pl_angle - FOV / 2;
	i = 0;
	while (i < WIN_W)
	{
		get_ray_collides_wall(&game->world, angle, ray_collides_wall);
		get_proj_points(&game->world, angle, ray_collides_wall, p_wall);
		assign_point_ints(p_wall[0], WIN_W - i - 1, p_wall[0][Y]);
		assign_point_ints(p_wall[1], WIN_W - i - 1, p_wall[1][Y]);
		draw_slice(game, p_wall, get_offset(game->world.tx_imgs,
				get_cardinal(ray_collides_wall), ray_collides_wall));
		angle += game->world.ray_angle;
		if (angle > 360)
			angle -= 360;
		i++;
	}
}

/**
 * init game draws background (ceiling and floor) +
 * added mlx_put_image_to_window
 */
void	draw_game(t_game *game)
{
	draw_bg_on_img(game->world.ceiling, game->world.floor, &game->img);
	draw_game_on_img(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlximg, 0, 0);
	debug ("-----------Hey! I get here!"); //
}
