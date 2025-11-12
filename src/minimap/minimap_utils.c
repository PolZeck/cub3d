/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:29:47 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/12 09:15:19 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

/**
 * @brief Draws a filled rectangle on the given image.
 * 
 * This function fills a rectangular area on the image `img` with the
 * specified color. Each pixel inside the rectangle is set individually
 * using `put_px`.
 * 
 * @param img Pointer to the image structure where pixels are drawn.
 * @param r Rectangle structure containing position, size, and color data.
 */
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

/**
 * @brief Returns the color associated with a given map cell character.
 * 
 * This function converts a map character into a color used on the minimap.
 * For example, '1' represents walls, ' ' represents empty space, and all
 * other characters are treated as floor tiles.
 * 
 * @param c Map cell character.
 * @return Corresponding color value in hexadecimal RGB format.
 */
int	color_for_cell(char c)
{
	if (c == '1')
		return (0x333333);
	if (c == ' ')
		return (0x000000);
	return (0xAAAAAA);
}

/**
 * @brief Draws a single row of tiles on the minimap.
 * 
 * This function iterates horizontally through the visible range of the map
 * and draws each tile of the specified row using the minimap context.
 * Each tile’s color is determined by the map character at that position.
 * 
 * @param a Pointer to the main application structure.
 * @param c Pointer to the minimap context structure.
 * @param y Map Y-coordinate of the row to draw.
 * @param dest_y Y-coordinate on the screen where the row will be drawn.
 */
void	minimap_draw_row(t_app *a, t_mmctx *c, int y, int dest_y)
{
	int	dx;
	int	dest_x;
	int	color;
	int	x;

	dx = -c->rad_x;
	while (dx <= c->rad_x)
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

/**
 * @brief Initializes the minimap drawing context.
 * 
 * This function sets up the `t_mmctx` structure with dimensions, offsets,
 * and player position data required for rendering the minimap. It determines
 * how many tiles are visible and their relative coordinates.
 * 
 * @param a Pointer to the main application structure.
 * @param c Pointer to the minimap context structure to initialize.
 * @param offx Horizontal offset of the minimap on screen.
 * @param offy Vertical offset of the minimap on screen.
 */
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
