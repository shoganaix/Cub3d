/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:54:43 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/03 11:29:11 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_slice(t_game *game, int p_wall[2][2], t_card cardinal, int offset)
{
	int		i;
	int		pixel_to_paint;
	t_color	color;

	i = p_wall[0][Y];
	while (i < p_wall[1][Y])
	{
		pixel_to_paint = i * WIN_W + p_wall[0][X];
		if (i < 0 || i >= WIN_H)
		{
			i ++;
			continue ;
		}
		color = read_pixel_from_image(game->world.tx_imgs[cardinal], offset, i);
		img_set_pixel_color(&game->img, pixel_to_paint, color, 1);
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
		draw_slice(game, p_wall, get_cardinal(ray_collides_wall),
			get_offset(game->world.tx_imgs,
				get_cardinal(ray_collides_wall), ray_collides_wall));
		angle = sum_degrees(angle, game->world.ray_angle);
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
	printf("PlayerR:%i inside cell[Y]: %i\n", grid_row(game->world.pl_point),
		game->world.pl_point[X] % CUB_SIZE); //
	printf("PlayerC:%i inside cell[X]: %i\n", grid_column(game->world.pl_point),
		game->world.pl_point[Y] % CUB_SIZE); //
	draw_game_on_img(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlximg, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.mlximg, 0, 0);
	draw_minimap_player(game);
	debug("🐸 DRAWN! 🐸"); //
}
