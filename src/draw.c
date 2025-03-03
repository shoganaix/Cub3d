/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:54:43 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/03 15:08:24 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// todo here
void	draw_slice(t_game *game, int wall_pts[2][2], t_card coll_wall, int offset)
{
	int		i;
	int		pixel_to_paint;
	t_color	color;

	i = wall_pts[0][Y];
	while (i < wall_pts[1][Y])
	{
		if (i < 0 || i >= WIN_H)
		{
			i++;
			continue ;
		}
		pixel_to_paint = i * WIN_W + wall_pts[0][X];
		color = read_pixel_from_image(game->world.tx_imgs[coll_wall],
				offset, i);
		img_set_pixel_color(&game->img, pixel_to_paint, color, 1);
		i++;
	}
}

void	draw_game_on_img(t_game *game)
{
	int			i;
	float		angle;
	int			ray_wall_coll_pt[2];
	int			wall_pts[2][2];
	t_card		coll_wall;

	ft_bzero(&ray_wall_coll_pt, sizeof(int) * 2);
	angle = game->world.pl_angle - FOV / 2;
	i = 0;
	while (i < WIN_W)
	{
		get_ray_wall_coll_pt(&game->world, angle, ray_wall_coll_pt, &coll_wall);
		get_projwall_pts_y(&game->world, angle, ray_wall_coll_pt, wall_pts);
		assign_point_ints(wall_pts[0], WIN_W - i - 1, wall_pts[0][Y]);
		assign_point_ints(wall_pts[1], WIN_W - i - 1, wall_pts[1][Y]);
		draw_slice(game, wall_pts, coll_wall,
			get_offset(game->world.tx_imgs, coll_wall, ray_wall_coll_pt));
		angle = sum_degrees(angle, game->world.ray_angle);
		i++;
	}
}

/**
 * this draws 
 * - background (ceiling and floor)
 * - game (maze)
 * - minimap
 * - minimap player position
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
