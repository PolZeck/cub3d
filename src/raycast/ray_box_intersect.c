/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_box_intersect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:47:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/12 10:51:49 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"
#include <math.h>

/**
 * @brief Safe reciprocal that avoids division by (near) zero.
 *
 * Returns 1.0 / v when |v| is large enough. When v is too close
 * to zero, returns a very large number with v's sign preserved.
 *
 * @param v Input value.
 * @return The reciprocal of v, or a large signed fallback (±1e30).
 */
static double	safe_inv(double v)
{
	double	sign;

	if (fabs(v) < 1e-12)
	{
		sign = 1.0;
		if (v < 0.0)
			sign = -1.0;
		return (copysign(1e30, sign));
	}
	return (1.0 / v);
}

/**
 * @brief Initialize slab bounds and inverse directions for a cell box.
 *
 * Sets the axis-aligned box [bx, bx+1] × [by, by+1] and precomputes
 * inverse ray directions using safe_inv.
 *
 * @param s  Output slab data (bounds and inv directions).
 * @param q  Ray-box query (origin, direction, cell coords).
 */
static void	init_slabs(t_slabs *s, const t_ray_box_query *q)
{
	s->minx = (double)q->bx;
	s->maxx = (double)q->bx + 1.0;
	s->miny = (double)q->by;
	s->maxy = (double)q->by + 1.0;
	s->invx = safe_inv(q->rd.x);
	s->invy = safe_inv(q->rd.y);
}

/**
 * @brief Compute t-interval (tmin, tmax) for a single axis slab.
 *
 * Given an axis-aligned min/max plane and the ray origin and inverse
 * direction on that axis, returns where the ray enters/exits the slab.
 *
 * @param in   Axis input (min, max, origin, invdir).
 * @param out  Axis output (tmin, tmax on this axis).
 */
static void	axis_t(const t_axis_in *in, t_axis_out *out)
{
	double	t1;
	double	t2;

	t1 = (in->minv - in->ro) * in->inv;
	t2 = (in->maxv - in->ro) * in->inv;
	out->tmin = fmin(t1, t2);
	out->tmax = fmax(t1, t2);
}

/**
 * @brief Combine X/Y intervals to resolve a 2D ray-box hit.
 *
 * Intersects the axis intervals to find the global enter/exit t.
 * If a valid intersection exists in front of the ray, sets the
 * enter t and which side was hit (0=X side, 1=Y side).
 *
 * @param in   Per-axis tmins/tmaxes for X and Y.
 * @param out  Hit data (t_enter and side).
 * @return 1 if the ray hits the box; 0 otherwise.
 */
static int	resolve_hit(const t_hit_in *in, t_hit_out *out)
{
	double	t_enter;
	double	t_exit;

	t_enter = fmax(in->tminx, in->tminy);
	t_exit = fmin(in->tmaxx, in->tmaxy);
	if (t_exit >= t_enter && t_exit > 0.0)
	{
		out->t_enter = t_enter;
		if (in->tminx > in->tminy)
			out->side = 0;
		else
			out->side = 1;
		return (1);
	}
	return (0);
}

/**
 * @brief Ray vs. grid-cell AABB intersection (2D slab method).
 *
 * Tests intersection between a ray and the axis-aligned unit cell
 * at (bx, by). On success, returns the entry distance and which
 * side was hit (0=vertical side, 1=horizontal side).
 *
 * @param q    Ray-box query (origin, direction, cell coords).
 * @param hit  Output hit (t_enter, side) if intersection occurs.
 * @return 1 on hit, 0 on miss.
 */
int	ray_box_intersect(const t_ray_box_query *q, t_ray_box_hit *hit)
{
	t_slabs		s;
	t_axis_out	ax;
	t_axis_out	ay;
	t_hit_in	hin;
	t_hit_out	hout;

	init_slabs(&s, q);
	axis_t(&(t_axis_in){s.minx, s.maxx, q->ro.x, s.invx}, &ax);
	axis_t(&(t_axis_in){s.miny, s.maxy, q->ro.y, s.invy}, &ay);
	hin = (t_hit_in){ax.tmin, ay.tmin, ax.tmax, ay.tmax};
	if (!resolve_hit(&hin, &hout))
		return (0);
	hit->t_enter = hout.t_enter;
	hit->side = hout.side;
	return (1);
}
