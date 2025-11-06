/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:29:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 15:38:22 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	fill_rect(t_img *img, t_rect r)
{
	int	i;
	int	j;

	if (!img || r.w <= 0 || r.h <= 0)
		return ;
	j = 0;
	while (j < r.h)
	{
		i = 0;
		while (i < r.w)
		{
			put_px(img, r.x + i, r.y + j, r.color);
			i++;
		}
		j++;
	}
}

int	color_for_cell(char c)
{
	if (c == '1')
		return (0x333333);
	if (c == ' ')
		return (0x000000);
	return (0xAAAAAA);
}

void	minimap_draw_row(t_app *a, t_mmctx *c, int y, int dest_y)
{
	int	dx;
	int	dest_x;
	int	color;
	int	x;

	dx = -c->rad_x;
	while (dx < c->rad_x)
	{
		x = c->cx + dx;
		dest_x = c->offx + (dx + c->rad_x) * c->tile;
		if (y >= 0 && y < a->cfg.map_h && x >= 0 && x < a->cfg.map_w)
			color = color_for_cell(a->cfg.map[y][x]);
		else
			color = 0x000000;
		fill_rect(&a->frame,
			(t_rect){dest_x, dest_y, c->tile, c->tile, color});
		dx++;
	}
}

void	mmctx_init(t_app *a, t_mmctx *c, int offx, int offy)
{
	c->tile = a->minimap.tile;
	if (c->tile > 0)
		c->vis_w = a->minimap.w / c->tile;
	else
		c->vis_w = 0;
	if (c->tile > 0)
		c->vis_h = a->minimap.h / c->tile;
	else
		c->vis_h = 0;
	c->offx = offx;
	c->offy = offy;
	c->rad_x = c->vis_w / 2;
	c->rad_y = c->vis_h / 2;
	c->cx = (int)a->pl.pos.x;
	c->cy = (int)a->pl.pos.y;
}
