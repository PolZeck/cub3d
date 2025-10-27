/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_post.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:22:57 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 12:58:31 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
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
	double	t;
	double	hx;
	double	hy;
	double	perp;

	t = r->t;
	hx = a->pl.pos_x + t * r->ray_dir_x;
	hy = a->pl.pos_y + t * r->ray_dir_y;
	perp = (hx - a->pl.pos_x) * a->pl.dir.x
		+ (hy - a->pl.pos_y) * a->pl.dir.y;
	if (perp < 1e-6)
		perp = 1e-6;
	r->perp_dist = perp;
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
