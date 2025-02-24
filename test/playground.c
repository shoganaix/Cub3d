/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   playground.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:10:39 by msoriano          #+#    #+#             */
/*   Updated: 2025/02/24 16:49:08 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

typedef struct	s_game {
	void	*mlx;
	void	*win;
}				t_game;

typedef struct	s_image
{
	void      *mlximg;
	char      *addr;
	int       bits_per_pixel;
	int       line_size;
	int       endian;
}   t_image;

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
    printf("Bye bye\n");
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

void paint_img(t_game game, char *img_path, int posX, int posY)
{
    t_image img;
	int		img_width;
	int		img_height;

    img.mlximg = mlx_xpm_file_to_image(game.mlx, img_path, &img_width, &img_height);
    mlx_put_image_to_window(game.mlx, game.win, img.mlximg, posX, posY);

}

int	main(void)
{
    t_game game;
    
    char	*img1 = "./img/xpm/test.xpm";
    char	*img2 = "./img/xpm/teapot.xpm";

    game.mlx = mlx_init();
    game.win = mlx_new_window(game.mlx, WIN_W, WIN_H, "CUB3D");

    paint_img(game, img1, 0, 0);
    paint_img(game, img2, 250, 250);

	mlx_hook(game.win, EVENT_KEYPRESS, 1L<<0, key_press_hndlr, &game);
    mlx_hook(game.win, EVENT_CLOSEWINDOW, 0, close_window, &game);
    mlx_loop(game.mlx);
    return(0);
}