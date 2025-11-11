/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:42:30 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:42:48 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

int	rgb24(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

/**
 * @brief Draw a single pixel on an image buffer.
 *
 * Writes a color value at pixel (x, y) in the given image, if
 * the coordinates are within bounds. The function uses the
 * image's internal address, line length, and bpp for offset.
 *
 * @param img   Pointer to the target image.
 * @param x     X-coordinate of the pixel.
 * @param y     Y-coordinate of the pixel.
 * @param color 24-bit color value (0xRRGGBB).
 */
void	put_px(t_img *img, int x, int y, int color)
{
	char	*p;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	p = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(int *)p = color;
}

/**
 * @brief Fill the frame background with ceiling and floor colors.
 *
 * Draws the top half of the frame using the ceiling color and the
 * bottom half using the floor color. This prepares the frame before
 * the 3D raycasting walls are drawn.
 *
 * @param a Application context (contains frame, colors, etc.).
 */
void	fill_half_screens(t_app *a)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < a->frame.h)
	{
		if (y < a->frame.h / 2)
			color = a->ceil_color;
		else
			color = a->floor_color;
		x = 0;
		while (x < a->frame.w)
		{
			put_px(&a->frame, x, y, color);
			x++;
		}
		y++;
	}
}
