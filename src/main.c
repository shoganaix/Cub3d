/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2025/01/09 17:12:33 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	main(void)
{
    t_game game;
    
    char	*img1 = "./img/test.xpm";
    char	*img2 = "./img/teapot.xpm";

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, VP_W, VP_H, "CUB3D");

    /**
     * 
     */
    paint_img(game, img1, 0, 0);
    paint_img(game, img2, 250, 250);
    /**
     * 
     */
	mlx_hook(game.win, EVENT_KEYPRESS, 1L<<0, key_press_hndlr, &game);
    mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);
    mlx_loop(game.mlx);
    return(0);
}