/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:08:15 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 15:38:22 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include <math.h>

static int	is_wall(t_app *a, int mx, int my)
{
	if (mx < 0 || my < 0 || mx >= a->cfg.map_w || my >= a->cfg.map_h)
		return (1);
	return (a->cfg.map[my][mx] == '1');
}

static void	move_fb(t_app *a, double spd)
{
	double	sign;
	double	nx;
	double	ny;

	sign = 1.0;
	if (a->key_s)
		sign = -1.0;
	if (!a->key_w && !a->key_s)
		return ;
	nx = a->pl.pos.x + a->pl.dir.x * spd * sign;
	ny = a->pl.pos.y + a->pl.dir.y * spd * sign;
	if (!is_wall(a, (int)nx, (int)a->pl.pos.y))
		a->pl.pos.x = nx;
	if (!is_wall(a, (int)a->pl.pos.x, (int)ny))
		a->pl.pos.y = ny;
}

static void	strafe_lr(t_app *a, double spd)
{
	double	sign;
	double	perp_x;
	double	perp_y;
	double	nx;
	double	ny;

	if (!a->key_a && !a->key_d)
		return ;
	sign = 1.0;
	if (a->key_a)
		sign = -1.0;
	perp_x = a->pl.dir.y;
	perp_y = -a->pl.dir.x;
	nx = a->pl.pos.x + perp_x * spd * sign;
	ny = a->pl.pos.y + perp_y * spd * sign;
	if (!is_wall(a, (int)nx, (int)a->pl.pos.y))
		a->pl.pos.x = nx;
	if (!is_wall(a, (int)a->pl.pos.x, (int)ny))
		a->pl.pos.y = ny;
}

static void	rotate_view(t_app *a, double rs)
{
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	if (!a->key_left && !a->key_right)
		return ;
	angle = rs;
	if (a->key_left)
		angle = -rs;
	old_dir_x = a->pl.dir.x;
	a->pl.dir.x = a->pl.dir.x * cos(angle) - a->pl.dir.y * sin(angle);
	a->pl.dir.y = old_dir_x * sin(angle) + a->pl.dir.y * cos(angle);
	old_plane_x = a->pl.plane.x;
	a->pl.plane.x = a->pl.plane.x * cos(angle) - a->pl.plane.y * sin(angle);
	a->pl.plane.y = old_plane_x * sin(angle) + a->pl.plane.y * cos(angle);
}

void	update_player(t_app *a, double move_speed, double rot_speed)
{
	move_fb(a, move_speed);
	strafe_lr(a, move_speed);
	rotate_view(a, rot_speed);
}
