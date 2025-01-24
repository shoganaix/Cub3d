/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/01/24 19:54:52 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*LIBS DEFINED*/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
//# include <mlx.h>
# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../libft/include/libft.h"

/* WINDOW */
# define VP_H		        1080			// viewport height
# define VP_W		        1920			// viewport width
# define WIN_NAME           ".:++### CUB3D ###++:."

typedef struct	s_game {
	void	*mlx;
	void	*win;
}				t_game;
typedef struct	s_color
{
	int r;
	int g;
	int b;
} t_color;

typedef enum e_card
{
	NO,
	SO,
	WE,
	EA,
	NUM_CARD
} t_card;

typedef struct	s_info
{
	char	*textures[4];
	t_color	floor;
	t_color ceiling;
}   t_info;

typedef struct	s_image
{
	void	*mlximg;
	char	*addr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
}   t_image;

int		close_window(t_game *game);
int		key_press_hndlr(int keycode, void *param);


void	paint_img(t_game game, char *img_path, int posX, int posY);

void	debug(char *msg);
void	debug_int(char *name_desc, int n);
void	debug_str(char *name_desc, char *str);

t_bool	check_args(int argn, char *args[]);

void	my_perror(char *msg);
void	my_perror_exit(char *msg);
void	my_perror_exit_st(char *msg, int err);
void	my_perr_arg(char *msg, char *var_name);
void	my_perr_arg_exit(char *msg, char *var_name);

void	init_info(t_info *info);
void	destroy_info(t_info *info);
void	show_info(t_info info);

t_bool check_map(char *cubfile, t_info *info);
t_bool check_texture(char *line, t_info *info, char *texture, t_card cp);
t_bool	check_color(char *line, t_info *info, char *item);
char *next_word(char *line, int *len);

/* EVENT */
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

/* KEYS */
# define KEY_A			97
# define KEY_S			KEY_A +  's' - 'a'
# define KEY_D			KEY_A +  'd' - 'a'
# define KEY_W			KEY_A +  'w' - 'a'

# define KEY_ESC		65307

# define KEY_LEFT		65361
# define KEY_UP			65362
# define KEY_RIGHT		65363
# define KEY_DOWN		65364

/* COLORS */
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

#endif