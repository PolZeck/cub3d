/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 10:26:16 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

void	ray_init(t_app *a, t_ray *r, int x)
{
	r->camera_x = 2.0 * x / (double)a->frame.w - 1.0;
	r->ray_dir = v2_add(a->pl.dir, v2_scale(a->pl.plane, r->camera_x));
	r->map_x = (int)a->pl.pos_x;
	r->map_y = (int)a->pl.pos_y;
	r->delta_x = (r->ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / r->ray_dir_x);
	r->delta_y = (r->ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / r->ray_dir_y);
	r->hit = 0;
}

void	ray_prepare_intersection(t_app *a, t_ray *r)
{
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_x = (a->pl.pos_x - r->map_x) * r->delta_x;
	}
	else
	{
		r->step_x = 1;
		r->side_x = (r->map_x + 1.0 - a->pl.pos_x) * r->delta_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_y = (a->pl.pos_y - r->map_y) * r->delta_y;
	}
	else
	{
		r->step_y = 1;
		r->side_y = (r->map_y + 1.0 - a->pl.pos_y) * r->delta_y;
	}
}
