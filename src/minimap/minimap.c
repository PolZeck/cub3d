/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:32:35 by lcosson           #+#    #+#             */
/*   Updated: 2025/10/30 14:14:20 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

/* --- petites briques --- */

static void	fill_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int j, i;

	if (!img || w <= 0 || h <= 0)
		return;
	for (j = 0; j < h; ++j)
		for (i = 0; i < w; ++i)
			put_px(img, x + i, y + j, color); // utilise la put_px fournie par ton runtime
}

static int	color_for_cell(char c)
{
	if (c == '1') return 0x333333;  // mur
	if (c == ' ') return 0x000000;  // padding hors-map
	return 0xAAAAAA;                // sol / spawn / vide
}

/* --- dessin des tuiles --- */

static void	draw_tiles(t_app *a, int offx, int offy)
{
	int y;

	y = 0;
	while (y < a->cfg.map_h && (y * a->minimap.tile) < a->minimap.h)
	{
		int x = 0;
		while (x < a->cfg.map_w && (x * a->minimap.tile) < a->minimap.w)
		{
			int cx = offx + x * a->minimap.tile;
			int cy = offy + y * a->minimap.tile;
			fill_rect(&a->frame, cx, cy, a->minimap.tile, a->minimap.tile,
				color_for_cell(a->cfg.map[y][x]));
			x++;
		}
		y++;
	}
}

/* --- joueur + direction --- */

static void	draw_player(t_app *a, int offx, int offy)
{
	int px = offx + (int)(a->pl.pos_x * a->minimap.tile);
	int py = offy + (int)(a->pl.pos_y * a->minimap.tile);

	/* point joueur */
	fill_rect(&a->frame, px - 2, py - 2, 4, 4, 0xFF0000);

	/* direction (petit point à l’extrémité du vecteur) */
	{
		int ex = px + (int)(a->pl.dir_x * (a->minimap.tile * 0.8));
		int ey = py + (int)(a->pl.dir_y * (a->minimap.tile * 0.8));
		fill_rect(&a->frame, ex - 1, ey - 1, 2, 2, 0xFFFF00);
	}
}

/* --- API --- */

void	minimap_draw(t_app *a)
{
	const int ox = a->minimap.margin_x;
	const int oy = a->minimap.margin_y;

	if (!a || !a->minimap.enabled)
		return;

	/* fond + bord */
	fill_rect(&a->frame, ox - 2, oy - 2, a->minimap.w + 4, a->minimap.h + 4, 0x000000);
	fill_rect(&a->frame, ox, oy, a->minimap.w, a->minimap.h, 0x202020);

	/* tuiles + joueur */
	draw_tiles(a, ox, oy);
	draw_player(a, ox, oy);
}
