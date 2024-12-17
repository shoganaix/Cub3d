/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2024/12/17 16:42:18 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

typedef struct	s_game {
	void	*mlx;
	void	*win;
}				t_game;

typedef struct	s_image
{
	void      *img;
	char      *addr;
	int       bits_per_pixel;
	int       line_size;
	int       endian;
}   t_image;

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
    // frees, destroys
    exit(0);
}

int	key_press_hndlr(int keycode, void *param)
{
    t_game *game;

    game = (t_game *)param;
    printf("key pressed %i\n", keycode);
    if (keycode == KEY_ESC)
        close_window(game);
    return (0);
}

int	main(void)
{
    t_game game;
    // t_image img;

    // char	*relative_path = "./test.xpm";
	// int		img_width;
	// int		img_height;
	
    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, 1920, 1080, "Hello world!");

    // img.img = mlx_xpm_file_to_image(game.mlx, relative_path, &img_width, &img_height);
    // img.addr = mlx_put_image_to_window(game.mlx, game.win, &img, 0, 0);

	mlx_hook(game.win, EVENT_KEYPRESS, 1L<<0, key_press_hndlr, &game);
    mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);
    mlx_loop(game.mlx);
    return(0);
}