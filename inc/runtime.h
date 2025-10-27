/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:24:23 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 11:03:36 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

#include "cub3d.h"
#include "mlx.h"
#include "raycast.h"
# include "vec2.h"
#include <math.h>



/* Keycodes (Linux/X11) */
#define KEY_ESC   65307
#define KEY_W     119
#define KEY_D     97
#define KEY_S     115
#define KEY_A     100
#define KEY_LEFT  65361
#define KEY_RIGHT 65363


typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_texset {
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_texset;

/* Player vectorisé */
typedef struct s_player {
	t_v2 pos;     /* à la place de pos_x/pos_y */
	t_v2 dir;     /* à la place de dir_x/dir_y */
	t_v2 plane;   /* à la place de plane_x/plane_y */
} t_player;

/* Ray vectorisé */
typedef struct s_ray {
	double	camera_x;
	t_v2	ray_dir;   /* remplace ray_dir_x / ray_dir_y */
	t_v2	delta;     /* remplace delta_x / delta_y     */
	t_v2	sdist;      /* remplace side_x / side_y        */
	int		map_x, map_y;
	int		step_x, step_y;
	int		hit;
	int		side;      /* 0: vertical, 1: horizontal */
	double	perp_dist;
	int		line_h;
	int		draw_start, draw_end;
} t_ray;


typedef struct s_app {
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	t_img		frame;
	int			ceil_color;
	int			floor_color;
	t_config	cfg;
	t_player	pl;
	int			key_w, key_a, key_s, key_d;
	int			key_left, key_right;
	t_texset	tex;
}	t_app;
	
typedef struct s_orient {
	double	dx;
	double	dy;
	double	px;
	double	py;
}	t_orient;

typedef enum e_face {
	FACE_NO, FACE_SO, FACE_WE, FACE_EA
}	t_face;


/* chargement / destruction */
int  load_textures(t_app *a);
void destroy_textures(t_app *a);

/* sampling */
int  texel_at(const t_img *tex, int u, int v);

/* API runtime */
int		run_app(t_config *cfg);

/* Hooks / player */
int		on_close(t_app *a);
int		on_key_down(int keycode, t_app *a);
int		on_key_up(int keycode, t_app *a);
int		on_loop(t_app *a);
void	init_player_from_cfg(t_app *a);
void	update_player(t_app *a, double move_speed, double rot_speed);
int		rgb24(int r, int g, int b);
void	put_px(t_img *img, int x, int y, int color);
void	fill_half_screens(t_app *a);

void	new_frame(t_app *a, int w, int h);
void	init_mlx_and_window(t_app *a);
void	setup_hooks(t_app *a);
void	init_player_from_cfg(t_app *a);
int		run_app(t_config *cfg);



#endif