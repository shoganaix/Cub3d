/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/01/09 17:32:13 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*LIBS DEFINED*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
//# include "mlx_linux/mlx.h"
//# include "../libft/libft.h"

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

int	close_window(t_game *game);
int	key_press_hndlr(int keycode, void *param);
void paint_img(t_game game, char *img_path, int posX, int posY);


# define VP_H		        1080			// viewport height
# define VP_W		        1920			// viewport width

# define EVENT_KEYPRESS		2
# define EVENT_KEYRELEASE	3
# define EVENT_MOUSEPRESS	4
# define EVENT_MOUSERELEASE	5
# define EVENT_MOUSEMOVE	6
# define EVENT_CLOSEWINDOW	17
# define MOUSE_LEFTCLICK	1
# define MOUSE_RIGHTCLICK	2
# define MOUSE_MIDCLICK		3
# define MOUSE_SCROLLUP		4
# define MOUSE_SCROLLDOWN	5

/* KEYS DEfINED*/

# define KEY_A			97
# define KEY_S			KEY_A +  's' - 'a'
# define KEY_D			KEY_A +  'd' - 'a'
# define KEY_W			KEY_A +  'w' - 'a'

// # define KEY_ESC		53
# define KEY_ESC		65307

# define KEY_L			123
# define KEY_R			124
# define KEY_DOWN		125
# define KEY_UP			126

#endif