/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:24:23 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 10:43:31 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUNTIME_H
# define RUNTIME_H

#include "cub3d.h"
#include "mlx.h"
#include <math.h>



/* Keycodes (Linux/X11) */
#define KEY_ESC   65307
#define KEY_W     119
#define KEY_A     97
#define KEY_S     115
#define KEY_D     100
#define KEY_LEFT  65361
#define KEY_RIGHT 65363

/* -------------------- Runtime -------------------- */


typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_player {
	double	pos_x, pos_y;   // position en cases (centre: +0.5)
	double	dir_x, dir_y;   // vecteur direction
	double	plane_x, plane_y; // vecteur plan (FOV ~66% -> 0.66)
}	t_player;

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
	// input
	int			key_w, key_a, key_s, key_d;
	int			key_left, key_right;
}	t_app;

/* API runtime */
int		run_app(t_config *cfg);

/* Draw / math */
int		rgb24(int r, int g, int b);
void	put_px(t_img *img, int x, int y, int color);
void	fill_half_screens(t_app *a); // fond plafond/sol

/* Hooks / player */
int		on_close(t_app *a);
int		on_key_down(int keycode, t_app *a);
int		on_key_up(int keycode, t_app *a);
int		on_loop(t_app *a);
void	init_player_from_cfg(t_app *a);
void	update_player(t_app *a, double move_speed, double rot_speed);

#endif