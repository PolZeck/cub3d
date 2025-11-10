/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:39:04 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/10 17:18:26 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

void	new_frame(t_app *a, int w, int h)
{
	a->frame.img = mlx_new_image(a->mlx, w, h);
	if (!a->frame.img)
		error_exit_app("Error\nmlx_new_image failed", a);
	a->frame.addr = mlx_get_data_addr(a->frame.img, &a->frame.bpp,
			&a->frame.line_len, &a->frame.endian);
	a->frame.w = w;
	a->frame.h = h;
	if (!a->frame.addr)
		error_exit_app("Error\nmlx_get_data_addr failed", a);
}

void	init_mlx_and_window(t_app *a, t_config *cfg)
{
	a->mlx = mlx_init();
	if (!a->mlx)
	{
		free_config(cfg);
		error_exit("Error\nmlx_init failed");
	}
	a->win = mlx_new_window(a->mlx, a->win_w, a->win_h, "cub3D");
	if (!a->win)
		error_exit_app("Error\nmlx_new_window failed", a);
	new_frame(a, a->win_w, a->win_h);
}
