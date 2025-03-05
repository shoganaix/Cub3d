/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:54:43 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/05 13:16:42 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// todo here
void	draw_proj_slice(t_game *game, float proj_wall_pts[2][2],
		t_card coll_wall, float cube_offset)
{
	int		i;
	int		img_offset[2];
	int		pixel_to_paint;
	t_color	color;
	t_image	img;

	img = game->world.tx_imgs[coll_wall];
	img_offset[X] = cube_offset * img.width / CUB_SIZE;
	i = proj_wall_pts[0][Y];
	while (i < proj_wall_pts[1][Y])
	{
		if (i < 0 || i >= WIN_H)
		{
			i++;
			continue ;
		}
		img_offset[Y] = (i - proj_wall_pts[0][Y]) * img.height / (proj_wall_pts[1][Y] - proj_wall_pts[0][Y]);
		pixel_to_paint = i * WIN_W + proj_wall_pts[0][X];
		color = read_pixel_from_image(img, img_offset);
		// if (i ==  WIN_H / 2)
		// {
		// 	ft_printf("painting x,y %i %i\n", proj_wall_pts[0][X], i);
		// 	printf("color %i %i %i\n", color.r, color.g, color.b); // 
		// }
		img_set_pixel_color(&game->img, pixel_to_paint, color, 1);
		i++;
	}
}

void	draw_game_on_img(t_game *game)
{
	int			i;
	float		angle;
	float			ray_wall_coll_pt[2];
	float			pt2[2];
	float			wall_pts[2][2];
	t_card		coll_wall;

	ft_bzero(&ray_wall_coll_pt, sizeof(int) * 2);
	assign_point(pt2, ray_wall_coll_pt);
	angle = game->world.pl_angle - FOV / 2;
	i = 0;
	while (i < WIN_W)
	{
		printf("x %i --\t ", i);
		get_ray_wall_coll_pt(&game->world, angle, ray_wall_coll_pt, &coll_wall);
		// if (pt2[X] != ray_wall_coll_pt[X] || pt2[Y] != ray_wall_coll_pt[Y])
		// 	debug_int(",,", i);
		assign_point(pt2, ray_wall_coll_pt);
		printf("coll_wall x,y %f %f\n", //
			1.0*ray_wall_coll_pt[X]/CUB_SIZE, //
			1.0*ray_wall_coll_pt[Y]/CUB_SIZE); //
		get_projwall_pts_y(&game->world, angle, ray_wall_coll_pt, wall_pts);
		assign_point_floats(wall_pts[0], WIN_W - i - 1, wall_pts[0][Y]);
		assign_point_floats(wall_pts[1], WIN_W - i - 1, wall_pts[1][Y]);
		draw_proj_slice(game, wall_pts, coll_wall,
			get_cube_offset(game->world.tx_imgs, coll_wall, ray_wall_coll_pt));
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
 * - player?
 */
void	draw_game(t_game *game)
{
	draw_bg_on_img(game->world.ceiling, game->world.floor, &game->img);
	printf("PlayerR:%i inside cell[Y]: %i\n", grid_row(game->world.pl_point),
		(int)game->world.pl_point[X] % CUB_SIZE); //
	printf("PlayerC:%i inside cell[X]: %i\n", grid_column(game->world.pl_point),
		(int)game->world.pl_point[Y] % CUB_SIZE); //
	draw_game_on_img(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlximg, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.mlximg, 0, 0);
	draw_minimap_player(game);
	mlx_pixel_put(game->mlx, game->win, 192, WIN_H / 2, 0xFF0000);
	mlx_pixel_put(game->mlx, game->win, 210, WIN_H / 2, 0xFF0000);
	debug("🐸 DRAWN! 🐸"); //
}
