/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturemap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:09:42 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 10:24:36 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

static double	wall_hit_x(const t_app *a, const t_ray *r)
{
	double	w;

	if (r->side == 0)
		w = a->pl.pos_y + r->perp_dist * r->ray_dir_y;
	else
		w = a->pl.pos_x + r->perp_dist * r->ray_dir_x;
	return (w - floor(w));
}

static int	tex_x_from_wall(const t_ray *r, const t_img *tex, double wall_x)
{
	int	tx;

	tx = (int)(wall_x * (double)tex->w);
	if (r->side == 0 && r->ray_dir_x > 0)
		tx = tex->w - tx - 1;
	if (r->side == 1 && r->ray_dir_y < 0)
		tx = tex->w - tx - 1;
	return (tx);
}

static void	span_init(const t_app *a, const t_ray *r, double step, t_span *sp)
{
	sp->y0 = r->draw_start;
	sp->y1 = r->draw_end;
	sp->tex_pos = (r->draw_start - (a->frame.h / 2 - r->line_h / 2)) * step;
	if (sp->y0 < 0)
	{
		sp->tex_pos += (-sp->y0) * step;
		sp->y0 = 0;
	}
	if (sp->y1 >= a->frame.h)
		sp->y1 = a->frame.h - 1;
}

static void	blit_span(t_app *a, int x, t_span *sp, t_drawctx *dc)
{
	int	y;
	int	tex_y;
	int	col;

	y = sp->y0;
	while (y <= sp->y1)
	{
		tex_y = (int)sp->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else if (tex_y >= dc->tex->h)
			tex_y = dc->tex->h - 1;
		col = texel_at(dc->tex, dc->tex_x, tex_y);
		if (dc->side)
			col = (col >> 1) & 0x7F7F7F;
		put_px(&a->frame, x, y, col);
		sp->tex_pos += dc->step;
		y++;
	}
}

void	draw_tex_column(t_app *a, int x, const t_ray *r)
{
	t_drawctx	dc;
	t_span		sp;

	dc.tex = get_tex(a, r);
	dc.tex_x = tex_x_from_wall(r, dc.tex, wall_hit_x(a, r));
	dc.side = r->side;
	dc.step = (double)dc.tex->h / (double)r->line_h;
	span_init(a, r, dc.step, &sp);
	blit_span(a, x, &sp, &dc);
}
