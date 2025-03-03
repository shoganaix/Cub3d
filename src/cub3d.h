/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macastro <macastro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 11:02:57 by msoriano          #+#    #+#             */
/*   Updated: 2025/03/03 13:08:10 by macastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* LIBS DEFINED */
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "../mlx_linux/mlx.h"
# include "../libft/include/libft.h"

# define DEBUG				1 						// debug flag

/* WINDOW */
# define WIN_NAME           ".:++### CUB3D ###++:."
# define WIN_H		        1080					// viewport height (pixels)
# define WIN_W		        1920					// viewport width (pixels)
# define CUB_SIZE           64						// cubes side in pixels
# define MM_CELL          	16						// minimap cells in pixels
# define FOV           		70						// field of view in degrees
# define R           		0						// row
# define C           		1						// column
# define X           		0						// x-axis
# define Y           		1						// y-axis
# define M_PI           	3.14159265358979323846  /* pi */
# define INT_MAX			2147483647

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef enum e_card
{
	NO,
	SO,
	WE,
	EA,
	NUM_CARD
}	t_card;

typedef enum e_moves
{
	FORW,
	BACKW,
	LEFT,
	RIGHT,
}	t_moves;

typedef enum e_errcode
{
	ERR_OK,
	ERR_ARGNUM,
	ERR_ARGFORMAT,
	ERR_ARGNOTFOUND,
	ERR_CUBINFOFORMAT,
	ERR_CUBINFOMISSING,
	ERR_CUBINFODUPPED,
	ERR_CUBINVALID,
	ERR_CUBINVALIDSPC,
	ERR_PLAYERNOTFOUND,
	ERR_CUBNOTCLOSED,
	ERR_MEM,
	NUM_ERR
}	t_errcode;

typedef struct s_image
{
	void	*mlximg;
	char	*addr;
	int		height;
	int		width;
	int		bits_per_pixel;
	int		line_size;		// bytes
	int		endian;
}	t_image;

typedef struct s_info
{
	char	*tx_paths[4];		// texture paths
	t_color	floor;
	t_color	ceiling;
}	t_info;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
	int		player_pos[2];		// player pos [r][c]
	t_card	player_or;			// orientation
}	t_map;

/* cub */
typedef struct s_cub
{
	t_info	info;
	t_map	smap;
}	t_cub;

/* world */
typedef struct s_world
{
	t_color	floor;
	t_color	ceiling;

	char	**map;			// grid
	int		map_height;		// grid height
	int		map_width;		// grid max width
	int		pl_height;
	int		pl_point[2];	// pixels [x][y]
	float	pl_angle;
	float	ray_angle;
	int		dist_to_plane;
	t_image	tx_imgs[4];	// texture images
}	t_world;

/* game */
typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_image	img;
	t_world	world;
	t_image	minimap;
	t_image	minimap_player;

}	t_game;

//Hooks
int			close_window(t_game *game);
int			key_press_hndlr(int keycode, void *param);

//Debug
void		debug(char *msg);
void		debug_int(char *name_desc, int n);
void		debug_str(char *name_desc, char *str);
void		debug_chr(char *name_desc, char c);
void		debug_float(char *name_desc, float f);

//Errors
void		my_perror(char *msg);
void		my_perror_exit(char *msg);
void		my_perror_exit_st(char *msg, int err);
void		my_perrorcode(t_errcode err, char *msg);
void		my_perrorcode_exit(t_errcode err, char *msg);
void		my_perr_arg(char *msg, char *var_name);
void		my_perr_arg_exit(char *msg, char *var_name);

//Cub & Info init
void		init_cub(t_cub *cub);
void		destroy_cub(t_cub *cub);
void		init_info(t_info *info);
void		destroy_info(t_info *info);
void		show_info(t_info info);

//Utils
char		*cardinal_to_str(t_card c);
int			cardinal_to_angle(t_card c);
t_card		char_to_cardinal(char c);
t_card		get_cardinal(int col_point[2]);

//Utils2
void		assign_point(int dst[2], int src[2]);
void		assign_point_ints(int dst[2], int x, int y);
int			grid_row(int point[2]);
int			grid_column(int point[2]);
float		sum_degrees(float deg1, float deg2);

//Parsing (Args, info & map)
void		check_args(int argn, char *args[]);
t_bool		can_open(const char *file_name);
t_errcode	read_cubfile(char *cubfile, t_cub *cub);
t_errcode	check_cub_info(int fd_in, t_info *info, char **line);
t_errcode	check_texture(char *line, t_info *info, t_card cp);
t_errcode	check_color(char *line, char *item, t_color *color);
char		*next_word(char *line, int *len);
t_bool		color_val_ok(char *s, int *v);
t_errcode	check_map_closed(t_cub *cub);
t_errcode	check_map_invalid_chars(t_cub *cub);
t_bool		is_inside_grid(char **grid, int r, int c, int grid_nrows);
char		**copy_map_arr(t_map m);
void		finish_gnl(int fd_in, char **line);

//Game
void		init_game(t_game *game, t_cub *cub);
void		destroy_game(t_game *game);

//Collision & Raycast
void		get_ray_wall_coll_pt(t_world *world, float ray, int coll_point[2],
				t_card *coll_card);
t_bool		ray_wall_loop(int p[2], int inc[2], t_world *world,
				int col_point[2]);
t_bool		pos_is_wall(int point[2], t_world *world);
t_bool		too_near_wall(int point[2], t_world *world);
float		dist_pts(int a[2], int b[2]);
void		assert_directions(float angle, int x_inc, int y_inc);
int			get_offset(t_image tx_img[4], t_card cardinal, int col_point[2]);
void		get_projwall_pts_y(t_world *world, float angle, int col_point[2],
				int pts[2][2]);

//Minimap
void		draw_minimap_player(t_game *game);
void		init_minimap(t_game *game);
void		set_minimap_cell(t_game *game, int r, int c, t_color color);
void		set_minimap_player(t_game *game, t_color color);

//Image and Draw
t_image		new_empty_img(void *mlx, int width_px, int height_px);
t_image		read_image(t_game *game, char *img_path);
t_color		read_pixel_from_image(t_image img, int offset, int cube_height);
void		img_set_pixel_color(t_image *img, int pixel,
				t_color color, int alpha);
void		draw_slice(t_game *game, int p_wall[2][2], t_card cardinal,
				int offset);
void		draw_bg_on_img(t_color ceiling, t_color floor, t_image *img);
void		draw_game(t_game *game);
void		paint_img(t_game game, char *img_path, int posX, int posY);

//Maths
float		ft_tan(float degrees);
float		ft_sin(float degrees);
float		ft_cos(float degrees);

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
# define KEY_S			115
# define KEY_D			100		// KEY_A +  'd' - 'a'
# define KEY_W			119		// KEY_A +  'w' - 'a'

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