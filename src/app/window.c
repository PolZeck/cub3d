/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:39:04 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:45:56 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

/**
 * @brief Create a new frame buffer image for rendering.
 *
 * Allocates a new image with the given dimensions using MiniLibX
 * and retrieves its address for pixel manipulation. If creation
 * or data address retrieval fails, the program exits cleanly.
 *
 * @param a Pointer to the application context.
 * @param w Width of the frame in pixels.
 * @param h Height of the frame in pixels.
 */
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

/**
 * @brief Initialize MiniLibX and create the main game window.
 *
 * Sets up the MLX connection, creates the game window, and allocates
 * the first frame buffer. If any of these steps fail, all resources
 * are freed and the program exits with an error message.
 *
 * @param a   Pointer to the application context.
 * @param cfg Pointer to the parsed configuration structure (used for cleanup).
 */
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
