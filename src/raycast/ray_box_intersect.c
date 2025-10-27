/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_box_intersect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 10:47:06 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 10:57:49 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"
#include <math.h>

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

static void	init_slabs(t_slabs *s, const t_ray_box_query *q)
{
	s->minx = (double)q->bx;
	s->maxx = (double)q->bx + 1.0;
	s->miny = (double)q->by;
	s->maxy = (double)q->by + 1.0;
	s->invx = safe_inv(q->rd.x);
	s->invy = safe_inv(q->rd.y);
}

static void	axis_t(const t_axis_in *in, t_axis_out *out)
{
	double	t1;
	double	t2;

	t1 = (in->minv - in->ro) * in->inv;
	t2 = (in->maxv - in->ro) * in->inv;
	out->tmin = fmin(t1, t2);
	out->tmax = fmax(t1, t2);
}

static int	resolve_hit(const t_hit_in *in, t_hit_out *out)
{
	double	tenter;
	double	texit;

	tenter = fmax(in->tminx, in->tminy);
	texit = fmin(in->tmaxx, in->tmaxy);
	if (texit >= tenter && texit > 0.0)
	{
		out->t_enter = tenter;
		if (in->tminx > in->tminy)
			out->side = 0;
		else
			out->side = 1;
		return (1);
	}
	return (0);
}

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
