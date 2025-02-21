/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:27:33 by macastro          #+#    #+#             */
/*   Updated: 2025/02/21 15:00:02 by macastro         ###   ########.fr       */
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
	game->world.pl_point[0] = cub->smap.player_pos[1] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_point[1] = cub->smap.player_pos[0] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_angle = cardinal_to_angle(cub->smap.player_or);
	game->world.ray_angle = WIN_W / FOV;
	game->world.dist_to_plane = WIN_W / 2 / ft_tan(FOV / 2);
	
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

void	draw_game_on_img(t_game *game)
{
	int	angle;
	int	i;
	int	ray_collides_wall[2];

	angle = game->world.pl_angle - FOV / 2;
	ft_bzero(&ray_collides_wall, sizeof(int) * 2);
	i = 0;
	while (i < WIN_W)
	{
		debug("************");
		debug_int("🌸angle", angle);
		debug_int("before collisionX", ray_collides_wall[0]);
		debug_int("before collisionY", ray_collides_wall[1]);
		get_ray_collides_wall(&game->world, angle, ray_collides_wall); // needs pl_pos and map
		debug_int("after collisionX", ray_collides_wall[0]);
		debug_int("after collisionY", ray_collides_wall[1]);
		debug_int("after collisionR", grid_row(ray_collides_wall));
		debug_int("after collisionC", grid_column(ray_collides_wall));
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
