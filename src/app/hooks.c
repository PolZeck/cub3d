/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 10:53:25 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
#include "runtime.h"
#include "raycast.h"

int	on_close(t_app *a)
{
	if (a->frame.img) mlx_destroy_image(a->mlx, a->frame.img);
	if (a->win) mlx_destroy_window(a->mlx, a->win);
	// mlx_destroy_display(a->mlx); // selon version, à activer si fourni
	free_config(&a->cfg);
	exit(0);
	return 0;
}

int	on_key_down(int key, t_app *a)
{
	if (key == KEY_ESC) return on_close(a);
	if (key == KEY_W) a->key_w = 1;
	if (key == KEY_A) a->key_a = 1;
	if (key == KEY_S) a->key_s = 1;
	if (key == KEY_D) a->key_d = 1;
	if (key == KEY_LEFT)  a->key_left = 1;
	if (key == KEY_RIGHT) a->key_right = 1;
	return 0;
}

int	on_key_up(int key, t_app *a)
{
	if (key == KEY_W) a->key_w = 0;
	if (key == KEY_A) a->key_a = 0;
	if (key == KEY_S) a->key_s = 0;
	if (key == KEY_D) a->key_d = 0;
	if (key == KEY_LEFT)  a->key_left = 0;
	if (key == KEY_RIGHT) a->key_right = 0;
	return 0;
}

static inline int is_wall(t_app *a, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= a->cfg.map_w || my >= a->cfg.map_h) return 1;
	return (a->cfg.map[my][mx] == '1');
}

void	update_player(t_app *a, double move_speed, double rot_speed)
{
	double old_dir_x, old_plane_x;
	double nx, ny;

	// déplacement avant/arrière
	if (a->key_w || a->key_s)
	{
		double sign = a->key_w ? 1.0 : -1.0;
		nx = a->pl.pos_x + a->pl.dir_x * move_speed * sign;
		ny = a->pl.pos_y + a->pl.dir_y * move_speed * sign;
		if (!is_wall(a, (int)nx, (int)a->pl.pos_y)) a->pl.pos_x = nx;
		if (!is_wall(a, (int)a->pl.pos_x, (int)ny)) a->pl.pos_y = ny;
	}
	// strafe gauche/droite
	if (a->key_a || a->key_d)
	{
		double sign = a->key_d ? 1.0 : -1.0;
		double perp_x = a->pl.dir_y;
		double perp_y = -a->pl.dir_x;
		nx = a->pl.pos_x + perp_x * move_speed * sign;
		ny = a->pl.pos_y + perp_y * move_speed * sign;
		if (!is_wall(a, (int)nx, (int)a->pl.pos_y)) a->pl.pos_x = nx;
		if (!is_wall(a, (int)a->pl.pos_x, (int)ny)) a->pl.pos_y = ny;
	}
	// rotation
	if (a->key_left || a->key_right)
	{
		double angle = rot_speed * (a->key_right ? 1.0 : -1.0);
		old_dir_x = a->pl.dir_x;
		a->pl.dir_x = a->pl.dir_x * cos(angle) - a->pl.dir_y * sin(angle);
		a->pl.dir_y = old_dir_x * sin(angle) + a->pl.dir_y * cos(angle);
		old_plane_x = a->pl.plane_x;
		a->pl.plane_x = a->pl.plane_x * cos(angle) - a->pl.plane_y * sin(angle);
		a->pl.plane_y = old_plane_x * sin(angle) + a->pl.plane_y * cos(angle);
	}
}

int	on_loop(t_app *a)
{
	const double move_speed = 0.08;
	const double rot_speed  = 0.05;

	update_player(a, move_speed, rot_speed);

	// dessine la scène
	render_frame(a);

	mlx_put_image_to_window(a->mlx, a->win, a->frame.img, 0, 0);
	return 0;
}
