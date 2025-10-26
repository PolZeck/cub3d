/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:42:30 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 12:42:37 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

int	rgb24(int r, int g, int b)
{
	return (((r & 0xFF) << 16) | ((g & 0xFF) << 8) | (b & 0xFF));
}

void	put_px(t_img *img, int x, int y, int color)
{
	char	*p;

	if (x < 0 || y < 0 || x >= img->w || y >= img->h)
		return ;
	p = img->addr + y * img->line_len + x * (img->bpp / 8);
	*(int *)p = color;
}

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
