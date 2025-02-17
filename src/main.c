/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/17 22:59:14 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * check args : nargs, extension
 * read map file .cub
 * init game
 * draw <---
 * insert_hooks(win, prog);
 * mlx_loop(mlx);
 */
int	main(int argc, char *argv[])
{
	t_game		game;
	t_errcode	e;
	// char		*img1 = "./img/test.xpm";
	// char		*img2 = "./img/teapot.xpm";

	// check args
	check_args(argc, argv);
	// map
	e = read_cubfile(argv[1], &game.cub);
	if (e != ERR_OK)
		my_perrorcode_exit(e, NULL);
	// world struct
	    //init_world(&game);
	// init
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, WIN_NAME);
	game.img = new_empty_img(game.mlx, WIN_W, WIN_H);

	// draw
	init_game(&game);
	// paint_img(game, img1, 0, 0);
	// paint_img(game, img2, 250, 250);

	// hooks // todo- add cub to game and free at EXIT by key/button
	mlx_hook(game.win, EVENT_KEYPRESS, 1L << 0, key_press_hndlr, &game);
	mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);

	mlx_loop(game.mlx);
	return (0);
}

