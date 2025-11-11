/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturemap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:09:42 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:41:19 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

/**
 * @brief Compute the fractional hit position on the wall.
 *
 * Determines how far along the wall the ray has hit, expressed as
 * a fraction in [0, 1). This is used to find the corresponding
 * horizontal coordinate within the texture.
 *
 * @param a Application context (player position).
 * @param r Ray data containing hit distance and side.
 * @return Fractional wall coordinate (0.0–1.0) for texture mapping.
 */
static double	wall_hit_x(const t_app *a, const t_ray *r)
{
	double	hx;
	double	hy;
	double	w;

	hx = a->pl.pos.x + r->t * r->ray_dir.x;
	hy = a->pl.pos.y + r->t * r->ray_dir.y;
	if (r->side == 0)
		w = hy - floor(hy);
	else
		w = hx - floor(hx);
	return (w);
}

/**
 * @brief Convert a fractional wall hit coordinate to a texture X index.
 *
 * Maps the wall hit fraction to the texture width and handles horizontal
 * flipping depending on the wall orientation and ray direction.
 *
 * @param r   Ray data (direction and side of hit).
 * @param tex Texture image of the hit wall.
 * @param wall_x Fractional hit position on the wall [0..1].
 * @return Texture X coordinate (column index) within the texture image.
 */
static int	tex_x_from_wall(const t_ray *r, const t_img *tex, double wall_x)
{
	int	tx;

	tx = (int)(wall_x * (double)tex->w);
	if (r->side == 0 && r->ray_dir.x > 0)
		tx = tex->w - tx - 1;
	if (r->side == 1 && r->ray_dir.y < 0)
		tx = tex->w - tx - 1;
	return (tx);
}

/**
 * @brief Initialize the vertical span and texture position for drawing.
 *
 * Calculates the start and end pixel positions on the screen and aligns
 * the initial texture position accordingly. Handles vertical clipping if
 * the wall slice extends beyond the screen bounds.
 *
 * @param a     Application context (for frame height).
 * @param r     Ray with projected draw range and line height.
 * @param step  Texture sampling step per screen pixel.
 * @param sp    Span data structure to fill (start, end, tex_pos).
 */
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

/**
 * @brief Render a vertical span of wall texture onto the frame buffer.
 *
 * Iterates through all screen pixels in the span, samples the correct
 * texel from the wall texture, applies a side shading for lighting, and
 * writes the resulting color into the frame image buffer.
 *
 * @param a  Application context (for frame buffer access).
 * @param x  Screen X coordinate of the column being drawn.
 * @param sp Span data (y range, texture position).
 * @param dc Drawing context (texture, step, side info).
 */
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

/**
 * @brief Draw one textured vertical column of the wall on the screen.
 *
 * Determines which texture to use based on the ray hit, computes the
 * corresponding horizontal texture coordinate, and renders the wall
 * column with perspective-correct sampling.
 *
 * @param a Application context (textures, frame buffer, player state).
 * @param x Screen column index (current ray index).
 * @param r Ray information (hit distance, side, line height, etc.).
 */
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
