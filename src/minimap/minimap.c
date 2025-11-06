/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:32:35 by lcosson           #+#    #+#             */
/*   Updated: 2025/11/06 15:20:09 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static void	draw_tiles_centered(t_app *a, int offx, int offy)
{
	t_mmctx	c;
	int		dy;

	mmctx_init(a, &c, offx, offy);
	if (c.tile <= 0 || c.vis_w <= 0 || c.vis_h <= 0)
		return ;
	dy = -c.rad_y;
	while (dy < c.rad_y)
	{
		minimap_draw_row(a, &c,
			c.cy + dy, c.offy + (dy + c.rad_y) * c.tile);
		dy++;
	}
}

static void	draw_player_centered_tile(t_app *a, int offx, int offy)
{
	int	tile;
	int	cx;
	int	cy;

	tile = a->minimap.tile;
	if (tile <= 0 || a->minimap.w <= 0 || a->minimap.h <= 0)
		return ;
	cx = offx + a->minimap.w / 2;
	cy = offy + a->minimap.h / 2;
	fill_rect(&a->frame, (t_rect){cx - 2, cy - 2, 4, 4, 0xFF0000});
	fill_rect(&a->frame, (t_rect){
		cx + (int)(a->pl.dir.x * (tile * 0.8)) - 1,
		cy + (int)(a->pl.dir.y * (tile * 0.8)) - 1,
		2, 2, 0xFFFF00});
}

void	minimap_draw(t_app *a)
{
	const int	ox = a->minimap.margin_x;
	const int	oy = a->minimap.margin_y;

	if (!a || !a->minimap.enabled)
		return ;
	fill_rect(&a->frame,
		(t_rect){ox - 2, oy - 2, a->minimap.w + 4, a->minimap.h + 4, 0x000000});
	fill_rect(&a->frame,
		(t_rect){ox, oy, a->minimap.w, a->minimap.h, 0x202020});
	draw_tiles_centered(a, ox, oy);
	draw_player_centered_tile(a, ox, oy);
}
