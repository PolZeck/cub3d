/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pol <pol@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:20:16 by pol               #+#    #+#             */
/*   Updated: 2025/11/06 13:23:42 by pol              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include <math.h>

static void rotate_angle(t_app *a, double angle)
{
	double old_dir_x;
	double old_plane_x;

	old_dir_x = a->pl.dir_x;
	old_plane_x = a->pl.plane_x;
	a->pl.dir_x = a->pl.dir_x * cos(angle) - a->pl.dir_y * sin(angle);
	a->pl.dir_y = old_dir_x * sin(angle) + a->pl.dir_y * cos(angle);
	a->pl.plane_x = a->pl.plane_x * cos(angle) - a->pl.plane_y * sin(angle);
	a->pl.plane_y = old_plane_x * sin(angle) + a->pl.plane_y * cos(angle);
}

static void mouse_recenter(t_app *a)
{
	a->mouse_warping = 1;
	a->mouse_last_x = a->center_x;
	a->mouse_last_y = a->center_y;
	mlx_mouse_move(a->mlx, a->win, a->center_x, a->center_y);
}

void mouse_enable(t_app *a, int enable)
{
	if (enable)
	{
		a->mouse_enabled = 1;
		a->mouse_inited = 1;
		a->center_x = a->win_w / 2;
		a->center_y = a->win_h / 2;
		mlx_mouse_hide(a->mlx, a->win);
		mouse_recenter(a);
	}
	else
	{
		a->mouse_enabled = 0;
		a->mouse_inited = 0;
		a->mouse_warping = 0;
		mlx_mouse_show(a->mlx, a->win);
	}
}

int on_mouse_move(int x, int y, t_app *a)
{
	int dx;

	(void)y;
	if (!a->mouse_enabled)
		return (0);
	if (a->mouse_warping)
	{
		a->mouse_warping = 0;
		return (0);
	}
	dx = x - a->center_x;
	if (dx != 0)
	{
		rotate_angle(a, (double)dx * a->mouse_sensi);
		mouse_recenter(a);
	}
	return (0);
}
