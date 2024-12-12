/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msoriano <msoriano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/12/03 13:34:21 by msoriano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	close_window(void *mlx)
{
	(void)mlx;
	exit(0);
}

int	key_press(int keycode, void *mlx)
{
    if (keycode == KEY_ESC) // Si la tecla es "Esc".
        close_window(mlx); // Llamar a la función de cierre.
    return (0);
}

int	main(void)
{
	void    *mlx;
	void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

    mlx_hook(mlx_win, 2, 1L << 0, key_press, mlx);
    mlx_hook(mlx_win, 17, 0, close_window, mlx);
    
    mlx_loop(mlx);
}