/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_post.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:22:57 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 11:31:54 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	side_tint(int base, int side)
{
	int	r;
	int	g;
	int	b;

	if (!side)
		return (base);
	b = (base & 0xFF) * 0.8;
	g = ((base >> 8) & 0xFF) * 0.8;
	r = ((base >> 16) & 0xFF) * 0.8;
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	ray_post(t_app *a, t_ray *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x == 0)
			r->perp_dist = 1e6;
		else
			r->perp_dist = (r->map_x - a->pl.pos_x
					+ (1 - r->step_x) / 2.0) / r->ray_dir_x;
	}
	else
	{
		if (r->ray_dir_y == 0)
			r->perp_dist = 1e6;
		else
			r->perp_dist = (r->map_y - a->pl.pos_y
					+ (1 - r->step_y) / 2.0) / r->ray_dir_y;
	}
	if (r->perp_dist < 1e-6)
		r->perp_dist = 1e-6;
	r->line_h = (int)(a->frame.h / r->perp_dist);
	r->draw_start = -r->line_h / 2 + a->frame.h / 2;
	r->draw_end = r->line_h / 2 + a->frame.h / 2;
}

int	column_color(t_ray *r)
{
	int	base;

	base = 0x55AAFF;
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			base = 0xFF4444;
		else
			base = 0x44FF44;
	}
	else
	{
		if (r->ray_dir_y > 0)
			base = 0x4444FF;
		else
			base = 0xFFFF44;
	}
	return (side_tint(base, r->side));
}
