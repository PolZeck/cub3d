/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/12 07:09:17 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

/**
 * @brief Handle window close event and free all resources.
 *
 * Called when the user closes the window or presses ESC. Destroys
 * all allocated MLX objects (image, window, display), frees the
 * configuration data and exits the program cleanly.
 *
 * @param a Pointer to the application context.
 * @return Always returns 0 (required by MLX hook convention).
 */
int	on_close(t_app *a)
{
	if (a->frame.img)
		mlx_destroy_image(a->mlx, a->frame.img);
	destroy_textures(a);
	if (a->win)
		mlx_destroy_window(a->mlx, a->win);
	mlx_destroy_display(a->mlx);
	free(a->mlx);
	free_config(&a->cfg);
	exit(0);
}

/**
 * @brief Set up all MLX event hooks and the main loop callback.
 *
 * Registers the functions handling key presses, key releases,
 * mouse movement, window close, and the continuous loop update.
 * These hooks ensure proper input handling and real-time updates.
 *
 * @param a Pointer to the application context.
 */
void	setup_hooks(t_app *a)
{
	mlx_hook(a->win, 17, 0, on_close, a);
	mlx_hook(a->win, 2, 1L << 0, on_key_down, a);
	mlx_hook(a->win, 3, 1L << 1, on_key_up, a);
	mlx_hook(a->win, EVT_MOTION, MSK_MOTION, on_mouse_move, a);
	mlx_loop_hook(a->mlx, on_loop, a);
}

/**
 * @brief Main loop executed every frame by MLX.
 *
 * Updates the player movement and rotation according to key input,
 * renders the 3D scene, draws the minimap, and displays the final
 * frame image on the window. This function is continuously called
 * by MLX while the window remains open.
 *
 * @param a Pointer to the application context.
 * @return Always returns 0 (required by MLX loop hook convention).
 */
int	on_loop(t_app *a)
{
	const double	move_speed = 0.05;
	const double	rot_speed = 0.05;

	update_player(a, move_speed, rot_speed);
	render_frame(a);
	minimap_draw(a);
	mlx_put_image_to_window(a->mlx, a->win, a->frame.img, 0, 0);
	return (0);
}
