/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 09:39:40 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:35:07 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"
#include <float.h>
#include <math.h>

/**
 * @brief Checks whether a map cell is a wall or out of bounds.
 *
 * Returns 1 if the (x, y) cell is outside the map rectangle or
 * if the map stores a '1' (wall) at that position. Returns 0
 * otherwise. Treating OOB as wall prevents escaping the map.
 *
 * @param a  Application context (provides map accessors).
 * @param x  Cell X coordinate.
 * @param y  Cell Y coordinate.
 * @return 1 if the cell is a wall or OOB, 0 otherwise.
 */
static int	is_wall(const t_app *a, int x, int y)
{
	if (x < 0 || y < 0 || x >= map_w(a) || y >= map_h(a))
		return (1);
	return (map_at(a, y, x) == '1');
}

/**
 * @brief Updates the ray with the currently best (closest) hit data.
 *
 * Copies distance t, hit cell (x, y), and hit side from the provided
 * update structure into the ray, replacing previous best values.
 *
 * @param r  Ray to update.
 * @param u  New best hit data (distance, cell, side).
 */
static void	update_best_hit(t_ray *r, const t_hit_update *u)
{
	r->t = u->t;
	r->map_x = u->x;
	r->map_y = u->y;
	r->side = u->side;
}

/**
 * @brief Tests a single map cell for ray-box intersection and
 *        updates the ray if this hit is closer than the current best.
 *
 * Uses the slab method via ray_box_intersect to compute the entry
 * distance into the unit box at (x, y). If the entry t is positive
 * and smaller than r->t, the ray's best hit is updated.
 *
 * @param a  Application context (player pos, etc.).
 * @param r  Ray to compare/update.
 * @param x  Cell X coordinate to test.
 * @param y  Cell Y coordinate to test.
 */
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

/**
 * @brief Finds the first (closest) wall hit for a ray by scanning
 *        all wall cells and keeping the minimum positive entry t.
 *
 * Initializes the ray with t = DBL_MAX (no hit). Iterates the map
 * grid; for each wall cell, performs an AABB ray test. If any hit
 * is found, sets r->hit = 1 and leaves r filled with the closest
 * impact distance, cell coordinates, and side.
 *
 * @param a  Application context (map and player state).
 * @param r  Ray to fill with hit information.
 */
void	ray_find_first_hit(t_app *a, t_ray *r)
{
	int	y;
	int	x;

	r->t = DBL_MAX;
	r->hit = 0;
	y = 0;
	while (y < map_h(a))
	{
		x = 0;
		while (x < map_w(a))
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
