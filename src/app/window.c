/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:39:04 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 12:39:10 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	new_frame(t_app *a, int w, int h)
{
	a->frame.img = mlx_new_image(a->mlx, w, h);
	if (!a->frame.img)
		error_exit("Error\nmlx_new_image failed");
	a->frame.addr = mlx_get_data_addr(\
		a->frame.img, &a->frame.bpp, &a->frame.line_len, &a->frame.endian);
	a->frame.w = w;
	a->frame.h = h;
	if (!a->frame.addr)
		error_exit("Error\nmlx_get_data_addr failed");
}

void	init_mlx_and_window(t_app *a)
{
	a->mlx = mlx_init();
	if (!a->mlx)
		error_exit("Error\nmlx_init failed");
	a->win = mlx_new_window(a->mlx, a->win_w, a->win_h, "cub3D");
	if (!a->win)
		error_exit("Error\nmlx_new_window failed");
	new_frame(a, a->win_w, a->win_h);
}
