/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/06 16:38:50 by msoriano         ###   ########.fr       */
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
 *      	call ft_putarr_str(game.world.map) to check
 * 3. init game + cub -> game
 * 3. draw <---
 * 4. insert_hooks(win, prog);
 *     mlx_hook(game.win, EVENT_KEYPRESS, 1L << 0,
 * 				key_press_hndlr, &game) calls while holding a key
 * 5. mlx_loop(mlx);
 */
int	main(int argc, char *argv[])
{
	t_game		game;
	t_cub		cub;

	check_args(argc, argv);
	read_cubfile_wrapper(argv[1], &cub);
	init_game(&game, &cub);
	draw_game(&game);
	mlx_key_hook(game.win, key_press_hndlr, &game);
	mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);
	mlx_loop(game.mlx);
	return (0);
}
