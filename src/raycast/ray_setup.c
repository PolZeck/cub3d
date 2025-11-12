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
#include "float.h"

/**
 * @brief Initialize the ray direction and reset its 
 * 	state for a given screen column.
 *
 * For the current column index @p x, compute the normalized camera coordinate
 * in the range [-1, 1] and derive the corresponding world-space ray direction
 * from the player's forward vector (@ref a->pl.dir) and camera plane
 * (@ref a->pl.plane). This defines the orientation of the ray that will be cast
 * into the world to find the first wall intersection.
 *
 * The function also resets all per-ray fields (hit flag, distance, side, etc.)
 * so subsequent stages (intersection, projection, drawing)
 * 	start from a clean state.
 *
 * @param a Application context containing player and frame data.
 * @param r Ray structure to initialize.
 * @param x Screen column index in the current frame (0 .. frame.w - 1).
 */
void	ray_init(t_app *a, t_ray *r, int x)
{
	double	camera_x;

	camera_x = (2.0 * x / (double)a->frame.w) - 1.0;
	r->ray_dir = v2_add(a->pl.dir, v2_scale(a->pl.plane, camera_x));
	r->t = DBL_MAX;
	r->hit = 0;
	r->side = 0;
}
