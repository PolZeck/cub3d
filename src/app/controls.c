/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:04:31 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:42:09 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include <math.h>

/**
 * @brief Handle key press events.
 *
 * Updates the movement and rotation flags when a key is pressed.
 * Handles exit on ESC and toggles mouse lock when Alt (left or right)
 * is pressed. These flags are later used to control player movement.
 *
 * @param key Keycode of the pressed key.
 * @param a   Application context (stores key state and mouse mode).
 * @return Always returns 0 (MLX event callback convention).
 */
int	on_key_down(int key, t_app *a)
{
	if (key == KEY_ESC)
		return (on_close(a));
	if (key == KEY_W)
		a->key_w = 1;
	if (key == KEY_A)
		a->key_a = 1;
	if (key == KEY_S)
		a->key_s = 1;
	if (key == KEY_D)
		a->key_d = 1;
	if (key == KEY_LEFT)
		a->key_left = 1;
	if (key == KEY_RIGHT)
		a->key_right = 1;
	if (key == KEY_ALT_L || key == KEY_ALT_R)
		mouse_enable(a, !a->mouse_enabled);
	return (0);
}

/**
 * @brief Handle key release events.
 *
 * Resets the movement and rotation flags when the corresponding
 * keys are released. This ensures movement stops when no key
 * is held down.
 *
 * @param key Keycode of the released key.
 * @param a   Application context (stores key state).
 * @return Always returns 0 (MLX event callback convention).
 */
int	on_key_up(int key, t_app *a)
{
	if (key == KEY_W)
		a->key_w = 0;
	if (key == KEY_A)
		a->key_a = 0;
	if (key == KEY_S)
		a->key_s = 0;
	if (key == KEY_D)
		a->key_d = 0;
	if (key == KEY_LEFT)
		a->key_left = 0;
	if (key == KEY_RIGHT)
		a->key_right = 0;
	return (0);
}
