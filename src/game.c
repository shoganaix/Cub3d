/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:27:33 by macastro          #+#    #+#             */
/*   Updated: 2025/03/06 16:35:54 by msoriano         ###   ########.fr       */
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
	game->world.map[cub->smap.player_pos[R]][cub->smap.player_pos[C]] = '0';
	game->world.map_height = cub->smap.height;
	game->world.map_width = cub->smap.width;
	game->world.ceiling = cub->info.ceiling;
	game->world.floor = cub->info.floor;
	game->world.pl_height = CUB_SIZE / 2.0;
	game->world.pl_point[X] = cub->smap.player_pos[C] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_point[Y] = cub->smap.player_pos[R] * CUB_SIZE + CUB_SIZE / 2;
	game->world.pl_angle = cardinal_to_angle(cub->smap.player_or);
	game->world.ray_angle = (1.0 * FOV) / WIN_W;
	game->world.dist_to_plane = WIN_W / 2 / ft_tan(FOV / 2);
	init_game_textures(game, cub);
	init_minimap(game);
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
	if (game->minimap.mlximg)
		mlx_destroy_image(game->mlx, game->minimap.mlximg);
	if (game->img.mlximg)
		mlx_destroy_image(game->mlx, game->img.mlximg);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
}

/**
 * using ray_angle and collision point, 
 * fills wall_pts (2 points) that are the upper 
 * and bottom point of the wall slice
 * 
 * beta
 * BETA is the angle of the ray that is being cast relative 
 * to the viewing angle (ray angle).
 * On the figure above, the viewing angle (ALPHA) is 90 degrees because 
 * the player is facing straight upward.
 * Because we have 60 degrees field of view, 
 * BETA is 30 degrees for the leftmost ray
 * and it is -30 degrees for the rightmost ray.
 */
void	get_projwall_pts_y(t_world *world, float ray_angle,
	float col_point[2], float wall_pts[2][2])
{
	const float	dist_to_proj = (WIN_W / 2) / ft_tan(FOV / 2);
	float		projwall_height;
	float		dist_to_wall_improved;
	float		angle_between;

	if (world->pl_angle >= ray_angle)
		angle_between = world->pl_angle - ray_angle;
	else
		angle_between = ray_angle - world->pl_angle;
	dist_to_wall_improved = dist_pts(world->pl_point, col_point)
		* ft_cos(angle_between);
	projwall_height = CUB_SIZE * dist_to_proj / dist_to_wall_improved;
	wall_pts[0][Y] = (WIN_H - projwall_height) / 2;
	wall_pts[1][Y] = WIN_H - wall_pts[0][Y];
}

/**
 * north/south wall -> use X axis
 * east/west wall -> use Y axis
 */
float	get_cube_offset(t_card wall, float col_point[2])
{
	float	offset;

	if (wall == NO || wall == SO)
		offset = (int)col_point[X] % CUB_SIZE;
	else
		offset = (int)col_point[Y] % CUB_SIZE;
	return (offset);
}
