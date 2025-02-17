/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 20:27:33 by macastro          #+#    #+#             */
/*   Updated: 2025/02/17 23:52:10 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO - check destroy game??
void	init_world(t_game *game)
{
	int	i;

	game->world.pl_height = CUB_SIZE / 2;
	game->world.pl_pos[0] = game->cub.smap.player_pos[0] * CUB_SIZE
		+ CUB_SIZE / 2;
	game->world.pl_pos[1] = game->cub.smap.player_pos[1] * CUB_SIZE
		+ CUB_SIZE / 2;
	game->world.pl_angle = cardinal_to_angle(game->cub.smap.player_or);

	game->world.ray_angle = WIN_W / FOV;
	game->world.dist_to_plane = WIN_W / 2 / tan(FOV / 2);

	i = 0;
	while (i < NUM_CARD)
	{
		game->world.textures[i] = mlx_xpm_file_to_image(game->mlx,
				game->cub.info.textures[i], NULL, NULL);
		if (!game->world.textures[i])
			return (destroy_cub(&game->cub),
				my_perror_exit("mlx_xpm_file_to_image failed"));
	}
}

void	init_game(t_game *game)
{
	debug("llego");
	draw_bg_on_img(game->cub.info.ceiling, game->cub.info.floor, &game->img);
}
