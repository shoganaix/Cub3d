/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/03 15:23:30 by msoriano         ###   ########.fr       */
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
	t_game	game;
	t_cub 	cub;
	char	*img1 = "./img/test.xpm";
	char	*img2 = "./img/teapot.xpm";
	t_errcode e;

	// check args
	e = check_args(argc, argv);
	if (e != ERR_OK)
		my_perrorcode_exit(e, NULL);
	// map
	e = check_cubfile(argv[1], &cub);
	if (e != ERR_OK)
		my_perrorcode_exit(e, NULL);
	// init
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, VP_W, VP_H, WIN_NAME);

	// draw
	paint_img(game, img1, 0, 0);
	paint_img(game, img2, 250, 250);

	// hooks
	mlx_hook(game.win, EVENT_KEYPRESS, 1L << 0, key_press_hndlr, &game);
	mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);

	mlx_loop(game.mlx);
	return (0);
}
