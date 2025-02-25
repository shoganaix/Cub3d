/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:54:43 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/25 17:27:37 by macastro         ###   ########.fr       */
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

void	set_minimap_player(t_game *game, t_color color)
{
	int	pixel;
	int	r;
	int	c;

	r = 0;
	while (r < game->minimap_player.height)
	{
		c = 0;
		while (c < game->minimap_player.width)
		{
			pixel = r * game->minimap_player.width + c;
			img_set_pixel_color(&game->minimap_player, pixel, color, 1);
			c++;
		}
		r++;
	}
}

void	set_minimap_cell(t_game *game, int r, int c, t_color color)
{
	const int	width = game->world.map_width * MM_CELL;
	int			pixel;
	int			i;
	int			j;

	i = 0;
	while (i < MM_CELL)
	{
		j = 0;
		while (j < MM_CELL)
		{
			pixel = (r * MM_CELL + i) * width + (c * MM_CELL + j);
			img_set_pixel_color(&game->minimap, pixel, color, 3);
			j++;
		}
		i++;
	}
}

void	init_minimap(t_game *game)
{
	int				r;
	int				c;
	const t_color	black = (t_color){.r = 0, .g = 0, .b = 0};
	const t_color	white = (t_color){.r = 255, .g = 255, .b = 255};
	const t_color	red = (t_color){.r = 255, .g = 0, .b = 0};

	game->minimap = new_empty_img(game->mlx, game->world.map_width * MM_CELL,
			game->world.map_height * MM_CELL);
	r = 0;
	while (r < game->world.map_height)
	{
		c = 0;
		while ((size_t)c < ft_strlen(game->world.map[r]))
		{
			if (game->world.map[r][c] == '1')
				set_minimap_cell(game, r, c, black);
			else if (game->world.map[r][c] == '0')
				set_minimap_cell(game, r, c, white);
			c++;
		}
		r++;
	}
	game->minimap_player = new_empty_img(game->mlx, MM_CELL / 2, MM_CELL / 2);
	set_minimap_player(game, red);

}

void draw_minimap_player(t_game *game)
{
	// TODO

	mlx_put_image_to_window(game->mlx, game->win, game->minimap_player.mlximg, 0, 0);


}

/**
 * init game draws background (ceiling and floor) +
 * added mlx_put_image_to_window
 */
void	draw_game(t_game *game)
{
	draw_bg_on_img(game->world.ceiling, game->world.floor, &game->img);
	printf("Player R:%i inside celly: %i\n", grid_row(game->world.pl_point), game->world.pl_point[X] % CUB_SIZE);
	printf("Player C:%i inside cellx: %i\n", grid_column(game->world.pl_point), game->world.pl_point[Y] % CUB_SIZE);
	draw_game_on_img(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.mlximg, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.mlximg, 0, 0);
	draw_minimap_player(game);
	debug("---------drawn!"); //
}
