/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:39:40 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 13:27:48 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"
#include <float.h>
#include <math.h>

static int	is_wall(const t_app *a, int x, int y)
{
	if (x < 0 || y < 0 || x >= MAP_W(a) || y >= MAP_H(a))
		return (1);
	return (MAP_AT(a, y, x) == '1');
}

static void	update_best_hit(t_ray *r, const t_hit_update *u)
{
	r->t = u->t;
	r->map_x = u->x;
	r->map_y = u->y;
	r->side = u->side;
}

static void	check_cell_hit(t_app *a, t_ray *r, int x, int y)
{
	t_ray_box_query	q;
	t_ray_box_hit	h;
	t_hit_update	u;

	q.ro = a->pl.pos;
	q.rd = r->ray_dir;
	q.bx = x;
	q.by = y;
	if (ray_box_intersect(&q, &h))
	{
		if (h.t_enter > 0.0 && h.t_enter < r->t)
		{
			u.t = h.t_enter;
			u.x = x;
			u.y = y;
			u.side = h.side;
			update_best_hit(r, &u);
		}
	}
}

void	ray_find_first_hit(t_app *a, t_ray *r)
{
	int	y;
	int	x;

	r->t = DBL_MAX;
	r->hit = 0;
	y = 0;
	while (y < MAP_H(a))
	{
		x = 0;
		while (x < MAP_W(a))
		{
			if (is_wall(a, x, y))
				check_cell_hit(a, r, x, y);
			x++;
		}
		y++;
	}
	if (r->t < DBL_MAX)
		r->hit = 1;
}
