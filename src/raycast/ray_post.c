/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_post.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+        */
/*   Created: 2025/10/22 11:22:57 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 15:20:09 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

/**
 * @brief Post-process a ray after intersection to compute projection.
 *
 * Converts the parametric hit distance t into a perpendicular distance
 * by projecting the hit vector onto the view direction. This avoids
 * fisheye distortion. Then computes the wall slice height and the
 * vertical draw range (draw_start/draw_end) on the screen.
 *
 * @param a Application context (player, frame size).
 * @param r Ray data to be updated (perp_dist, line_h, draw bounds).
 */
void	ray_post(t_app *a, t_ray *r)
{
	double	t;
	double	hx;
	double	hy;
	double	perp;

	t = r->t;
	hx = a->pl.pos.x + t * r->ray_dir.x;
	hy = a->pl.pos.y + t * r->ray_dir.y;
	perp = (hx - a->pl.pos.x) * a->pl.dir.x
		+ (hy - a->pl.pos.y) * a->pl.dir.y;
	if (perp < 1e-6)
		perp = 1e-6;
	r->perp_dist = perp;
	r->line_h = (int)(a->frame.h / r->perp_dist);
	r->draw_start = -r->line_h / 2 + a->frame.h / 2;
	r->draw_end = r->line_h / 2 + a->frame.h / 2;
}
