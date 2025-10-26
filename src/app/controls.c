/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:04:31 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 13:08:32 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include <math.h>

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
	return (0);
}

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
