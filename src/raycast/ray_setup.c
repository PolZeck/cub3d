/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+        :+:   */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 16:00:07 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

/**
 * @brief Initialize per-column ray parameters from camera geometry.
 *
 * Converts the screen column x into a camera-space coordinate in [-1, 1],
 * builds the world-space ray direction from player dir/plane, initializes
 * the starting map cell, and precomputes delta distances for grid stepping.
 * The hit flag is cleared so later stages can record the first impact.
 *
 * @param a Application context (player, frame size).
 * @param r Output ray structure to initialize.
 * @param x Screen column index (0..frame.w-1).
 */
void	ray_init(t_app *a, t_ray *r, int x)
{
	r->camera_x = 2.0 * x / (double)a->frame.w - 1.0;
	r->ray_dir = v2_add(a->pl.dir, v2_scale(a->pl.plane, r->camera_x));
	r->map_x = (int)a->pl.pos.x;
	r->map_y = (int)a->pl.pos.y;
	if (r->ray_dir.x == 0.0)
		r->delta.x = 1e30 ;
	else
		r->delta.x = fabs(1.0 / r->ray_dir.x);
	if (r->ray_dir.y == 0.0)
		r->delta.y = 1e30 ;
	else
		r->delta.y = fabs(1.0 / r->ray_dir.y);
	r->hit = 0;
}

/**
 * @brief Prepare initial side distances and step directions for DDA.
 *
 * Based on the ray direction components, computes the step (+1/-1) on
 * each axis and the initial side distances (sdist) from the player to
 * the first vertical/horizontal grid line. These values are used by a
 * classic DDA walk or for compatible intersection logic.
 *
 * @param a Application context (player position).
 * @param r Ray structure with ray_dir, map cell, and delta filled.
 */
void	ray_prepare_intersection(t_app *a, t_ray *r)
{
	if (r->ray_dir.x < 0)
	{
		r->step_x = -1;
		r->sdist.x = (a->pl.pos.x - r->map_x) * r->delta.x;
	}
	else
	{
		r->step_x = 1;
		r->sdist.x = (r->map_x + 1.0 - a->pl.pos.x) * r->delta.x;
	}
	if (r->ray_dir.y < 0)
	{
		r->step_y = -1;
		r->sdist.y = (a->pl.pos.y - r->map_y) * r->delta.y;
	}
	else
	{
		r->step_y = 1;
		r->sdist.y = (r->map_y + 1.0 - a->pl.pos.y) * r->delta.y;
	}
}
