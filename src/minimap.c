/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:43:49 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/06 17:03:39 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	const t_color	black = (t_color){.r = 30, .g = 30, .b = 30};

	game->minimap = new_empty_img(game->mlx, game->world.map_width * MM_CELL,
			game->world.map_height * MM_CELL);
	r = 0;
	while (r < game->world.map_height)
	{
		c = 0;
		while (c < game->world.map_width)
		{
			if ((size_t)c < ft_strlen(game->world.map[r])
				&& game->world.map[r][c] == '1')
				set_minimap_cell(game, r, c, black);
			else if ((size_t)c < ft_strlen(game->world.map[r])
				&& game->world.map[r][c] == '0')
				set_minimap_cell(game, r, c, game->world.ceiling);
			else
				set_minimap_cell(game, r, c, black);
			c++;
		}
		r++;
	}
	game->minimap_player = new_empty_img(game->mlx, MM_CELL, MM_CELL);
	set_minimap_player(game, game->world.floor);
}

void	draw_minimap_player(t_game *game)
{
	int	player_x;
	int	player_y;
	int	draw_x;
	int	draw_y;

	player_x = (game->world.pl_point[X] * MM_CELL) / CUB_SIZE;
	player_y = (game->world.pl_point[Y] * MM_CELL) / CUB_SIZE;
	draw_x = player_x - (game->minimap_player.width / 2);
	draw_y = player_y - (game->minimap_player.height / 2);
	mlx_put_image_to_window(game->mlx, game->win,
		game->minimap_player.mlximg, draw_x, draw_y);
}
