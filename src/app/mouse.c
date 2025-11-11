/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 12:20:16 by pol               #+#    #+#             */
/*   Updated: 2025/11/11 13:44:10 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include <math.h>

/**
 * @brief Rotate the player's view by a given angle.
 *
 * Rotates both the direction and camera plane vectors using a 2D
 * rotation matrix. This function preserves the vector lengths and
 * ensures the FOV remains constant during mouse movement.
 *
 * @param a      Pointer to the application context.
 * @param angle  Rotation angle in radians (positive = right turn).
 */
static void	rotate_angle(t_app *a, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = a->pl.dir.x;
	old_plane_x = a->pl.plane.x;
	a->pl.dir.x = a->pl.dir.x * cos(angle) - a->pl.dir.y * sin(angle);
	a->pl.dir.y = old_dir_x * sin(angle) + a->pl.dir.y * cos(angle);
	a->pl.plane.x = a->pl.plane.x * cos(angle) - a->pl.plane.y * sin(angle);
	a->pl.plane.y = old_plane_x * sin(angle) + a->pl.plane.y * cos(angle);
}

/**
 * @brief Center the mouse cursor back to the screen midpoint.
 *
 * Updates the internal mouse state to mark the cursor as recentered
 * and calls the MLX function to move it to the window center.
 *
 * @param a Pointer to the application context.
 */
static void	mouse_recenter(t_app *a)
{
	a->mouse_warping = 1;
	a->mouse_last_x = a->center_x;
	a->mouse_last_y = a->center_y;
	mlx_mouse_move(a->mlx, a->win, a->center_x, a->center_y);
}

/**
 * @brief Enable or disable mouse-based camera control.
 *
 * When enabled, the mouse is hidden and locked to the window center.
 * When disabled, the cursor is released and visible. Used to toggle
 * between free mouse mode and FPS-style look control.
 *
 * @param a       Pointer to the application context.
 * @param enable  1 to enable mouse control, 0 to disable.
 */
void	mouse_enable(t_app *a, int enable)
{
	if (enable)
	{
		a->mouse_enabled = 1;
		a->mouse_inited = 1;
		a->center_x = a->win_w / 2;
		a->center_y = a->win_h / 2;
		mlx_mouse_hide(a->mlx, a->win);
		mouse_recenter(a);
	}
	else
	{
		a->mouse_enabled = 0;
		a->mouse_inited = 0;
		a->mouse_warping = 0;
		mlx_mouse_show(a->mlx, a->win);
	}
}

/**
 * @brief Handle mouse movement for camera rotation.
 *
 * Detects horizontal mouse displacement and converts it into a
 * rotation of the player's view. The mouse is continuously reset
 * to the window center after movement to simulate infinite rotation.
 *
 * @param x Current mouse X position.
 * @param y Current mouse Y position (unused).
 * @param a Pointer to the application context.
 * @return Always returns 0 (MLX event callback convention).
 */
int	on_mouse_move(int x, int y, t_app *a)
{
	int	dx;

	(void)y;
	if (!a->mouse_enabled)
		return (0);
	if (a->mouse_warping)
	{
		a->mouse_warping = 0;
		return (0);
	}
	dx = x - a->center_x;
	if (dx != 0)
	{
		rotate_angle(a, (double)dx * a->mouse_sensi);
		mouse_recenter(a);
	}
	return (0);
}
