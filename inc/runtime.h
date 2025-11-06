/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pol <pol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:24:23 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 13:25:21 by pol              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
#define RUNTIME_H

#include "cub3d.h"
#include "mlx.h"
#include "raycast.h"
#include "vec2.h"
#include <math.h>

#define MINIMAP_TILE 8
#define MINIMAP_W 200
#define MINIMAP_H 200
#define MINIMAP_MARGIN_X 10
#define MINIMAP_MARGIN_Y 10

#define EVT_MOTION 6
#define MSK_MOTION (1L << 6)

#ifndef KEY_ALT_L
#define KEY_ALT_L 65513
#endif
#ifndef KEY_ALT_R
#define KEY_ALT_R 65514
#endif

#define KEY_ESC 65307
#define KEY_W 119
#define KEY_D 97
#define KEY_S 115
#define KEY_A 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363

typedef struct s_minimap
{
	int enabled;
	int tile;
	int w;
	int h;
	int margin_x;
	int margin_y;
} t_minimap;

typedef struct s_img
{
	void *img;
	char *addr;
	int bpp;
	int line_len;
	int endian;
	int w;
	int h;
} t_img;

typedef struct s_texset
{
	t_img no;
	t_img so;
	t_img we;
	t_img ea;
} t_texset;

typedef struct s_player
{
	t_v2 pos;
	t_v2 dir;
	t_v2 plane;
} t_player;

typedef struct s_ray
{
	double camera_x;
	t_v2 ray_dir;
	t_v2 delta;
	t_v2 sdist;
	int map_x, map_y;
	int step_x, step_y;
	int hit;
	int side;
	double t;
	double perp_dist;
	int line_h;
	int draw_start, draw_end;
} t_ray;

typedef struct s_app
{
	void *mlx;
	void *win;
	int win_w;
	int win_h;
	t_img frame;
	int ceil_color;
	int floor_color;
	t_config cfg;
	t_player pl;
	int key_w, key_a, key_s, key_d;
	int key_left, key_right;
	t_texset tex;
	t_minimap minimap;
	int mouse_enabled;
	int mouse_inited;
	int mouse_last_x;
	int mouse_last_y;
	double mouse_sensi;
	int mouse_warping;
	int center_x;
	int center_y;
} t_app;

typedef struct s_orient
{
	double dx;
	double dy;
	double px;
	double py;
} t_orient;

typedef enum e_face
{
	FACE_NO,
	FACE_SO,
	FACE_WE,
	FACE_EA
} t_face;

int load_textures(t_app *a);
void destroy_textures(t_app *a);

int texel_at(const t_img *tex, int u, int v);

int run_app(t_config *cfg);

int on_close(t_app *a);
int on_key_down(int keycode, t_app *a);
int on_key_up(int keycode, t_app *a);
int on_loop(t_app *a);
void init_player_from_cfg(t_app *a);
void update_player(t_app *a, double move_speed, double rot_speed);
int rgb24(int r, int g, int b);
void put_px(t_img *img, int x, int y, int color);
void fill_half_screens(t_app *a);

void new_frame(t_app *a, int w, int h);
void init_mlx_and_window(t_app *a);
void setup_hooks(t_app *a);
void init_player_from_cfg(t_app *a);
int run_app(t_config *cfg);
int on_mouse_move(int x, int y, t_app *a);
void mouse_enable(t_app *a, int enable);

void minimap_draw(t_app *a);

#endif