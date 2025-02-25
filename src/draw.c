/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:54:43 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/25 15:18:49 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * TO DO:
 * El problema esta en que no entra en el bucle porque nuestro
 * 	p_wall[0][Y] (la i) > p_wall[1][Y]
 */
void	draw_slice(t_game *game, int p_wall[2][2], t_card cardinal, int offset)
{
	int		i;
	int		pixel_to_paint;
	t_color	color;

		// printf("i INIT: %d\n", p_wall[0][Y]); //
		// printf("i FIN: %d\n", p_wall[1][Y]); //

		
	i = p_wall[0][Y];
	while (i < p_wall[1][Y])
	{
		pixel_to_paint = i * WIN_W + p_wall[0][X];
		// printf("p_wall[0][X]: %i", p_wall[0][X]);
		// printf("Nuestra i es: %i", i);
		if (i < 0 || i >= WIN_H)
		{
			//my_perror("Height fuera de rango.");
			i ++;
			continue;
		}
		color = read_pixel_from_image(game->world.tx_imgs[cardinal], offset, i);
		//printf("Color: R=%i, G=%i, B=%i\n", color.r, color.g, color.b); //
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
		//printf("angle %f\n", angle);
		get_ray_collides_wall(&game->world, angle, ray_collides_wall);
		get_proj_points(&game->world, angle, ray_collides_wall, p_wall);
		assign_point_ints(p_wall[0], WIN_W - i - 1, p_wall[0][Y]);
		assign_point_ints(p_wall[1], WIN_W - i - 1, p_wall[1][Y]);
		// debug_int("PWALL[0] EN Y", p_wall[0][Y]); //
		// debug_int("PWALL[1] EN Y", p_wall[1][Y]); //

		draw_slice(game, p_wall, get_cardinal(ray_collides_wall),
			get_offset(game->world.tx_imgs,
				get_cardinal(ray_collides_wall), ray_collides_wall));
		angle += game->world.ray_angle;
		if (angle > 360)
			angle -= 360;
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int			r;
	int			c;
	t_image		map_img;
	int			pixel;

	map_img = new_empty_img(game->mlx, game->world.map_width,
			game->world.map_height);
	debug_int("game->world.map_width", game->world.map_width);
	debug_int("game->world.map_height", game->world.map_height);
	r = 0;
	while (r < game->world.map_height)
	{
		c = 0;
		while ((size_t)c < ft_strlen(game->world.map[r]))
		{
			debug_int("r", r);
			debug_int("c", c);
			pixel = r * game->world.map_height + c;
			if (game->world.map[r][c] == '1')
				img_set_pixel_color(&map_img, pixel, (t_color)
				{.r = 0, .g = 0, .b = 0});
			else if (game->world.map[r][c] == '0')
				img_set_pixel_color(&map_img, pixel, (t_color)
				{.r = 255, .g = 255, .b = 255});
			c++;
		}
		r++;
	}
	debug("llego");
	mlx_put_image_to_window(game->mlx, game->win, map_img.mlximg, 0, 0);
	debug("llegox3");
}


/**
 * init game draws background (ceiling and floor) +
 * added mlx_put_image_to_window
 */
void	draw_game(t_game *game)
{
	draw_bg_on_img(game->world.ceiling, game->world.floor, &game->img);
	printf("Player R:%i inside cell: %i\n", grid_row(game->world.pl_point), game->world.pl_point[X] % CUB_SIZE);
	printf("Player C:%i inside cell: %i\n", grid_column(game->world.pl_point), game->world.pl_point[Y] % CUB_SIZE);
	draw_game_on_img(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlximg, 0, 0);
	//draw_minimap(game);
	debug ("-----------Hey! I get here!"); //
}
