/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/19 15:39:31 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * check args : nargs, extension
 * read map file .cub -> cub
 * init game + cub -> game
 * draw <---
 * insert_hooks(win, prog);
 * mlx_loop(mlx);
 */
int	main(int argc, char *argv[])
{
	t_game		game;
	t_cub		cub;
	t_errcode	e;

	// check args
	check_args(argc, argv);
	// map
	e = read_cubfile(argv[1], &cub);
	if (e != ERR_OK)
		my_perrorcode_exit(e, NULL);
	// init
	init_game(&game, &cub);
	// draw
	draw_game(&game);
	// paint_img(game, img1, 0, 0);
	// paint_img(game, img2, 250, 250);

	// hooks // todo- add cub to game and free at EXIT by key/button
	mlx_hook(game.win, EVENT_KEYPRESS, 1L << 0, key_press_hndlr, &game);
	mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);

	mlx_loop(game.mlx);
	return (0);
}

