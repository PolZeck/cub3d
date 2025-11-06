/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:24:23 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 16:00:33 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

# include "cub3d.h"
# include "mlx.h"
# include "minimap.h"
# include "raycast.h"
# include "vec2.h"
# include <math.h>

# define EVT_MOTION 6
# define MSK_MOTION 64L
# define KEY_ALT_L 65513
# define KEY_ALT_R 65514
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_D 97
# define KEY_S 115
# define KEY_A 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

typedef struct s_minimap	t_minimap;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_texset
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
}	t_texset;

typedef struct s_player
{
	t_v2	pos;
	t_v2	dir;
	t_v2	plane;
}	t_player;

typedef struct s_ray
{
	double	camera_x;
	t_v2	ray_dir;
	t_v2	delta;
	t_v2	sdist;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	t;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	int			win_w;
	int			win_h;
	t_img		frame;
	int			ceil_color;
	int			floor_color;
	t_config	cfg;
	t_player	pl;
	int			key_w;
	int			key_a;
	int			key_s;
	int			key_d;
	int			key_left;
	int			key_right;
	t_texset	tex;
	t_minimap	minimap;
	int			mouse_enabled;
	int			mouse_inited;
	int			mouse_last_x;
	int			mouse_last_y;
	double		mouse_sensi;
	int			mouse_warping;
	int			center_x;
	int			center_y;
}	t_app;

typedef struct s_orient
{
	double	dx;
	double	dy;
	double	px;
	double	py;
}	t_orient;

typedef enum e_face
{
	FACE_NO,
	FACE_SO,
	FACE_WE,
	FACE_EA
}	t_face;

int		load_textures(t_app *a);
void	destroy_textures(t_app *a);
int		texel_at(const t_img *tex, int u, int v);
int		run_app(t_config *cfg);
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
int		on_mouse_move(int x, int y, t_app *a);
void	mouse_enable(t_app *a, int enable);

#endif