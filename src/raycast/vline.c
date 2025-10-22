/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vline.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:52:15 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 11:30:18 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	draw_vline(t_img *img, t_vline v)
{
	int	y;

	if (v.x < 0 || v.x >= img->w)
		return ;
	if (v.y0 < 0)
		v.y0 = 0;
	if (v.y1 >= img->h)
		v.y1 = img->h - 1;
	y = v.y0;
	while (y <= v.y1)
	{
		put_px(img, v.x, y, v.color);
		y++;
	}
}
