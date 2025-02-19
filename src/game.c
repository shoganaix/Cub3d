/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:27:33 by macastro          #+#    #+#             */
/*   Updated: 2025/02/19 20:26:21 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_textures(t_game *game, t_cub *cub)
{
	int		i;
	int		w;
	int		h;
	char	*imgpath;

	i = 0;
	while (i < NUM_CARD)
	{
		imgpath = cub->info.tx_paths[i];
		if (!can_open(imgpath))
			return (destroy_cub(cub), destroy_game(game),
				my_perror_exit("textures files not found"));
		game->world.tx_imgs[i] = mlx_xpm_file_to_image(game->mlx,
				imgpath, &w, &h);
		if (game->world.tx_imgs[i] == NULL)
			return (destroy_cub(cub), destroy_game(game),
				my_perror_exit("mlx_xpm_file_to_image failed"));
		i++;
	}
}

void	init_game(t_game *game, t_cub *cub)
{
	ft_bzero(game, sizeof(t_game));
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIN_W, WIN_H, WIN_NAME);
	game->img = new_empty_img(game->mlx, WIN_W, WIN_H);
	game->world.map = copy_map_arr(cub->smap);
	if (game->world.map == NULL)
		return (destroy_cub(cub), destroy_game(game),
			my_perrorcode_exit(ERR_MEM, NULL));
	game->world.map_height = cub->smap.height;
	game->world.ceiling = cub->info.ceiling;
	game->world.floor = cub->info.floor;
	game->world.pl_height = CUB_SIZE / 2;
	game->world.pl_pos[0] = cub->smap.player_pos[0] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_pos[1] = cub->smap.player_pos[1] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_angle = cardinal_to_angle(cub->smap.player_or);
	game->world.ray_angle = WIN_W / FOV;
	game->world.dist_to_plane = WIN_W / 2 / tan(FOV / 2);
	
	init_game_textures(game, cub);
	destroy_cub(cub);
}

void	destroy_game(t_game *game)
{
	int	i;

	if (game->world.map != NULL)
		ft_free_arrstr(game->world.map);
	i = 0;
	while (i < NUM_CARD)
	{
		if (game->world.tx_imgs[i] != NULL)
			mlx_destroy_image(game->mlx, game->world.tx_imgs[i]);
		i++;
	}
	if (game->img.mlximg)
		mlx_destroy_image(game->mlx, game->img.mlximg);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// destroy: img, win, mlx
}

t_bool	pos_is_wall(int pos[2], t_world *world)
{
	int	grid_pos[2];

	grid_pos[0] = floor(pos[0] / CUB_SIZE);
	grid_pos[1] = floor(pos[1] / CUB_SIZE);
	debug_int("grid 0", grid_pos[0]);
	debug_int("grid 1", grid_pos[1]);
	return (world->map[grid_pos[1]][grid_pos[0]] == '1');
}
void	ray_collides_wall_vert(t_world *world, int angle, int col_point[2])
{
	int		a[2];
	int		y_inc;
	int		x_inc;

	y_inc = CUB_SIZE * tan(angle);
	while (TRUE)
	{
		if (90 < angle && angle < 270) // ==?
		{
			a[0] = floor(world->pl_pos[0] / CUB_SIZE) * CUB_SIZE - 1;
			x_inc = -1 * CUB_SIZE;
		}
		else
		{
			a[0] = floor(world->pl_pos[0] / CUB_SIZE) * CUB_SIZE + 64;
			x_inc = CUB_SIZE;
		}
		a[1] = world->pl_pos[1] + (world->pl_pos[0] - a[0]) * tan(angle);
		if (pos_is_wall(a, world))
			break ;
		a[0] += x_inc;
		a[1] += y_inc;
	}
	col_point[0] = a[0];
	col_point[1] = a[1];
}

void	ray_collides_wall_hori(t_world *world, int angle, int col_point[2])
{
	int		a[2];
	int		y_inc;
	int		x_inc;

	x_inc = CUB_SIZE / tan(angle);
	while (TRUE)
	{
		if (0 < angle && angle < 180) // ==?
		{
			a[1] = floor(world->pl_pos[1] / CUB_SIZE) * CUB_SIZE - 1;
			y_inc = -1 * CUB_SIZE;
		}
		else
		{
			a[1] = floor(world->pl_pos[1] / CUB_SIZE) * CUB_SIZE + 64;
			y_inc = CUB_SIZE;
		}
		a[0] = world->pl_pos[0] + (world->pl_pos[1] - a[1])/tan(angle);
		if (pos_is_wall(a, world))
			break ;
		a[0] += x_inc;
		a[1] += y_inc;
	}
	col_point[0] = a[0];
	col_point[1] = a[1];
}

int	dist_between_points(int a[2], int b[2])
{
	return (floor(sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2))));
}

void	get_ray_collides_wall(t_world *world, int angle, int point[2])
{
	int	vert_collision[2];
	int	hori_collision[2];
	int	dh;
	int	dv;

	debug("v--------------");
	ray_collides_wall_vert(world, angle, vert_collision);
	debug("h----------------");
	ray_collides_wall_hori(world, angle, hori_collision);

	// point =  el mas cercano al jugador
	dh = dist_between_points(world->pl_pos, hori_collision);
	dv = dist_between_points(world->pl_pos, vert_collision);
	if (dh <= dv)
	{
		point[0] = hori_collision[0];
		point[1] = hori_collision[1];
	}
	else
	{
		point[0] = vert_collision[0];
		point[1] = vert_collision[1];
	}
}

void	draw_game_on_img(t_game *game)
{
	int angle;
	int	i;
	int	ray_collides_wall[2];

	angle = game->world.pl_angle - FOV / 2;
	i = 0;
	while (i < WIN_W)
	{
		debug("************");
		debug_int("**player 0", game->world.pl_pos[0]);
		debug_int("**player 1", game->world.pl_pos[1]);
		debug_int("**angle", angle);
		get_ray_collides_wall(&game->world, angle, ray_collides_wall); // needs pl_pos and map

		// ...
		angle += game->world.ray_angle;
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
}
