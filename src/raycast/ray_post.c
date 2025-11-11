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
 * @brief Apply a simple shading based on the hit side.
 *
 * For side==0, returns the base color unchanged. For side==1,
 * darkens the RGB components by a constant factor to simulate
 * directional lighting and add depth contrast.
 *
 * @param base Base RGB color (0xRRGGBB).
 * @param side Hit side flag (0=primary, 1=secondary).
 * @return Shaded color in 0xRRGGBB format.
 */
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

/**
 * @brief Produce a debug wall color based on face and apply side tint.
 *
 * Assigns a distinct base color per cardinal face (E/W/N/S) using the
 * ray direction and hit side, then darkens it for secondary sides via
 * side_tint. Useful when textures are unavailable or for debugging.
 *
 * @param r Ray containing side and direction information.
 * @return Final RGB color (0xRRGGBB) for the current column.
 */
int	column_color(t_ray *r)
{
	int	base;

	base = 0x55AAFF;
	if (r->side == 0)
	{
		if (r->ray_dir.x > 0)
			base = 0xFF4444;
		else
			base = 0x44FF44;
	}
	else
	{
		if (r->ray_dir.y > 0)
			base = 0x4444FF;
		else
			base = 0xFFFF44;
	}
	return (side_tint(base, r->side));
}
