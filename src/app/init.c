/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:21 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/23 10:08:42 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
#include "runtime.h"

static void	new_frame(t_app *a, int w, int h)
{
	a->frame.img = mlx_new_image(a->mlx, w, h);
	if (!a->frame.img) error_exit("Error\nmlx_new_image failed");
	a->frame.addr = mlx_get_data_addr(a->frame.img, &a->frame.bpp,
		&a->frame.line_len, &a->frame.endian);
	a->frame.w = w; a->frame.h = h;
	if (!a->frame.addr) error_exit("Error\nmlx_get_data_addr failed");
}

int	rgb24(int r, int g, int b) { return ((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF); }

void	put_px(t_img *img, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= img->w || y >= img->h) return;
	char *p = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(int *)p = color;
}

void	init_player_from_cfg(t_app *a)
{
	a->pl.pos_x = a->cfg.player_x + 0.5;
	a->pl.pos_y = a->cfg.player_y + 0.5;
	if (a->cfg.player_dir == 'N') { a->pl.dir_x = 0;  a->pl.dir_y = -1; a->pl.plane_x = 0.66; a->pl.plane_y = 0; }
	if (a->cfg.player_dir == 'S') { a->pl.dir_x = 0;  a->pl.dir_y = 1;  a->pl.plane_x = -0.66; a->pl.plane_y = 0; }
	if (a->cfg.player_dir == 'E') { a->pl.dir_x = 1;  a->pl.dir_y = 0;  a->pl.plane_x = 0; a->pl.plane_y = 0.66; }
	if (a->cfg.player_dir == 'W') { a->pl.dir_x = -1; a->pl.dir_y = 0;  a->pl.plane_x = 0; a->pl.plane_y = -0.66; }
}

void	fill_half_screens(t_app *a)
{
	for (int y = 0; y < a->frame.h; ++y)
	{
		int color = (y < a->frame.h / 2) ? a->ceil_color : a->floor_color;
		for (int x = 0; x < a->frame.w; ++x)
			put_px(&a->frame, x, y, color);
	}
}

int	run_app(t_config *cfg)
{
	t_app a;
	ft_bzero(&a, sizeof(a));
	a.cfg = *cfg; // shallow copy (on ne double-free pas cfg derrière)
	a.win_w = 1024; a.win_h = 768;

	a.ceil_color  = rgb24(cfg->ceiling.r, cfg->ceiling.g, cfg->ceiling.b);
	a.floor_color = rgb24(cfg->floor.r,   cfg->floor.g,   cfg->floor.b);

	a.mlx = mlx_init(); if (!a.mlx) error_exit("Error\nmlx_init failed");
	a.win = mlx_new_window(a.mlx, a.win_w, a.win_h, "cub3D"); if (!a.win) error_exit("Error\nmlx_new_window failed");
	new_frame(&a, a.win_w, a.win_h);
	init_player_from_cfg(&a);
	load_textures(&a);

	mlx_hook(a.win, 17, 0, on_close, &a);           // croix rouge
	mlx_hook(a.win, 2, 1L<<0, on_key_down, &a);     // KeyPress
	mlx_hook(a.win, 3, 1L<<1, on_key_up, &a);       // KeyRelease
	mlx_loop_hook(a.mlx, on_loop, &a);

	mlx_loop(a.mlx);
	return 0;
}
