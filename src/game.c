/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:27:33 by macastro          #+#    #+#             */
/*   Updated: 2025/02/25 15:02:27 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game_textures(t_game *game, t_cub *cub)
{
	int		i;
	char	*imgpath;

	i = 0;
	while (i < NUM_CARD)
	{
		imgpath = cub->info.tx_paths[i];
		if (!can_open(imgpath))
			return (destroy_cub(cub), destroy_game(game),
				my_perror_exit("textures files not found"));
		game->world.tx_imgs[i] = read_image(game, imgpath);
		if (game->world.tx_imgs[i].height != game->world.tx_imgs[i].width)
			return (destroy_cub(cub), destroy_game(game),
				my_perror_exit("xpm_file is not a square"));
		if (game->world.tx_imgs[i].mlximg == NULL)
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
	game->world.map_width = cub->smap.width;
	game->world.ceiling = cub->info.ceiling;
	game->world.floor = cub->info.floor;
	game->world.pl_height = CUB_SIZE / 2;
	game->world.pl_point[0] = cub->smap.player_pos[1] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_point[1] = cub->smap.player_pos[0] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_angle = cardinal_to_angle(cub->smap.player_or);
	game->world.ray_angle = (1.0 * FOV) / WIN_W;
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
		if (game->world.tx_imgs[i].mlximg != NULL)
			mlx_destroy_image(game->mlx, game->world.tx_imgs[i].mlximg);
		i++;
	}
	if (game->img.mlximg)
		mlx_destroy_image(game->mlx, game->img.mlximg);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	// destroy: img, win, mlx
}

/**
 * using angle and collision point, 
 * fills pts (2 points) that are the upper and bottom point of the wall slice
 * 
 * beta
 * BETA is the angle of the ray that is being cast relative to the viewing angle.
 * On the figure above, the viewing angle (ALPHA) is 90 degrees because 
 * the player is facing straight upward.
 * Because we have 60 degrees field of view, 
 * BETA is 30 degrees for the leftmost ray
 * and it is -30 degrees for the rightmost ray.
 */
void	get_proj_points(t_world *world, float angle,
	int col_point[2], int pts[2][2])
{
	const int	dist_to_plane = (WIN_W / 2) / ft_tan(FOV / 2);
	int			proj_wall_height;
	int			real_ray_len;

	if (world->pl_angle >= angle)
		real_ray_len = dist_between_points(world->pl_point, col_point)
			* ft_cos(world->pl_angle - angle);
	else
		real_ray_len = dist_between_points(world->pl_point, col_point)
			* ft_cos(angle - world->pl_angle);
	proj_wall_height = CUB_SIZE * dist_to_plane / real_ray_len;
	//debug_int("proj_wall_height", proj_wall_height);
	pts[0][Y] = WIN_H / 2 - proj_wall_height / 2;
	pts[1][Y] = WIN_H - pts[0][Y];
}

int	get_offset(t_image tx_img[4], t_card cardinal, int col_point[2])
{
	int	offset;

	if (cardinal == NO || cardinal == SO)
		offset = col_point[X] % tx_img[cardinal].height;
	else
		offset = col_point[Y] % tx_img[cardinal].height;
	return (offset);
}
