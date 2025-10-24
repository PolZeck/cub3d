/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:09 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/24 07:46:01 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	render_frame(t_app *a)
{
	int		x;
	t_ray	r;
	// int		color;
	// t_vline	v;

	fill_half_screens(a);
	x = 0;
	while (x < a->frame.w)
	{
		ray_init(a, &r, x);
		dda_init(a, &r);
		dda_run(a, &r);
		ray_post(a, &r);
		/* ==== colonne texturée à la place des couleurs unies ==== */
		{
			t_face		face;
			const t_img	*tex;
			double		wall_x;
			int			tex_x;
			double		step;
			double		tex_pos;
			int			y;
			int			tex_y;
			int			col;
			t_vline		v;

			/* 1) choisir la face (NO/SO/WE/EA) */
			face = pick_face(r.side, r.ray_dir_x, r.ray_dir_y);
			tex = (face == FACE_NO) ? &a->tex.no
				: (face == FACE_SO) ? &a->tex.so
				: (face == FACE_WE) ? &a->tex.we : &a->tex.ea;

			/* 2) coordonnée mur X locale [0..1) */
			if (r.side == 0)
				wall_x = a->pl.pos_y + r.perp_dist * r.ray_dir_y;
			else
				wall_x = a->pl.pos_x + r.perp_dist * r.ray_dir_x;
			wall_x -= floor(wall_x);

			/* 3) tex_x + flips pour garder la texture droite */
			tex_x = (int)(wall_x * (double)tex->w);
			if (r.side == 0 && r.ray_dir_x > 0)
				tex_x = tex->w - tex_x - 1;
			if (r.side == 1 && r.ray_dir_y < 0)
				tex_x = tex->w - tex_x - 1;

			/* 4) sampling vertical */
			v.x = x;
			v.y0 = r.draw_start;
			v.y1 = r.draw_end;
			if (v.y0 < 0)
				v.y0 = 0;
			if (v.y1 >= a->frame.h)
				v.y1 = a->frame.h - 1;
			step = (double)tex->h / (double)r.line_h;
			tex_pos = (r.draw_start - (a->frame.h / 2 - r.line_h / 2)) * step;
			if (r.draw_start < 0)
				tex_pos += (-r.draw_start) * step;
			y = v.y0;
			while (y <= v.y1)
			{
				tex_y = (int)tex_pos;
				tex_pos += step;
				col = texel_at(tex, tex_x, tex_y);
				/* petit ombrage sur les murs Y pour le relief */
				if (r.side)
					col = (col >> 1) & 0x7F7F7F;
				put_px(&a->frame, v.x, y, col);
				y++;
			}
		}
		x++;
	}
	return (0);
}
