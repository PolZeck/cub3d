/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 13:32:35 by lcosson           #+#    #+#             */
/*   Updated: 2025/10/30 15:00:56 by lcosson          ###   ########.fr       */
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

/* --- tuiles autour du joueur, centrées --- */
static void draw_tiles_centered(t_app *a, int offx, int offy)
{
	int tile, vis_w, vis_h, rad_x, rad_y;
	int cy, cx;
	int dy, dx;

	tile = a->minimap.tile;
	vis_w = a->minimap.w / tile;
	vis_h = a->minimap.h / tile;
	if (tile <= 0 || vis_w <= 0 || vis_h <= 0)
		return;

	rad_x = vis_w / 2;
	rad_y = vis_h / 2;

	cx = (int)a->pl.pos_x;
	cy = (int)a->pl.pos_y;

	dy = -rad_y;
	while (dy < rad_y)
	{
		int y = cy + dy;
		int dest_y = offy + (dy + rad_y) * tile;

		dx = -rad_x;
		while (dx < rad_x)
		{
			int x = cx + dx;
			int dest_x = offx + (dx + rad_x) * tile;
			int color;

			if (y >= 0 && y < a->cfg.map_h && x >= 0 && x < a->cfg.map_w)
				color = color_for_cell(a->cfg.map[y][x]);
			else
				color = 0x000000;

			fill_rect(&a->frame, dest_x, dest_y, tile, tile, color);
			dx++;
		}
		dy++;
	}
}

/* --- joueur centré sur SA CASE minimap --- */
static void draw_player_centered_tile(t_app *a, int offx, int offy)
{
	int tile = a->minimap.tile;
	int vis_w = a->minimap.w / tile;
	int vis_h = a->minimap.h / tile;

	if (tile <= 0 || vis_w <= 0 || vis_h <= 0)
		return;

	/* indice de la tuile centrale dans la fenêtre (col, row) */
	/* NB: si vis_w/vis_h sont pairs, on choisit la tuile "de gauche/haut" du centre */
	int center_col = vis_w / 2;
	int center_row = vis_h / 2;

	/* centre pixel de cette tuile centrale */
	int cx = offx + center_col * tile + tile / 2;
	int cy = offy + center_row * tile + tile / 2;

	/* point joueur au centre de SA case */
	fill_rect(&a->frame, cx - 2, cy - 2, 4, 4, 0xFF0000);

	/* petit marqueur de direction à partir du centre de cette case */
	{
		int ex = cx + (int)(a->pl.dir_x * (tile * 0.8));
		int ey = cy + (int)(a->pl.dir_y * (tile * 0.8));
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

	/* version centrée */
	draw_tiles_centered(a, ox, oy);
	draw_player_centered_tile(a, ox, oy);
}
