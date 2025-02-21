/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/21 14:57:34 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


void	read_cubfile_wrapper(char *cubfile, t_cub *cub)
{
	t_errcode	e;

	e = read_cubfile(cubfile, cub);
	if (e != ERR_OK)
		my_perrorcode_exit(e, "Error in cub map.");
}

/**
 * PROGRAM PARTS:
 * 1. check args : nargs, file extension, ..
 * 2. read map file .cub -> cub
 * 3. init game + cub -> game
 * 3. draw <---
 * 4. insert_hooks(win, prog);
 * 5. mlx_loop(mlx);
 */
int	main(int argc, char *argv[])
{
	t_game		game;
	t_cub		cub;

	check_args(argc, argv);
	read_cubfile_wrapper(argv[1], &cub);
	
	init_game(&game, &cub);
	
	ft_putarr_str(game.world.map); //
	debug_int("**player x", game.world.pl_point[0]);
	debug_int("**player y", game.world.pl_point[1]);
	ft_printf("player r:%i c:%i\n", grid_row(game.world.pl_point), grid_column(game.world.pl_point));
	//ft_printf("%c\n", game.world.map[2][1]);
	// ft_printf("%c\n", game.world.map[3][0]);
	// ft_printf("%c\n", game.world.map[1][1]);
	// ft_printf("%c\n", game.world.map[0][4]);
	// ft_printf("%c\n", game.world.map[1][0]);

	draw_game(&game);
	// paint_img(game, img1, 0, 0);


	mlx_hook(game.win, EVENT_KEYPRESS, 1L << 0, key_press_hndlr, &game);
	mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);

	mlx_loop(game.mlx);
	return (0);
}

