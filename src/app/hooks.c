/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/30 14:08:43 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

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

void	setup_hooks(t_app *a)
{
	mlx_hook(a->win, 17, 0, on_close, a);
	mlx_hook(a->win, 2, 1L << 0, on_key_down, a);
	mlx_hook(a->win, 3, 1L << 1, on_key_up, a);
	mlx_loop_hook(a->mlx, on_loop, a);
}

int	on_loop(t_app *a)
{
	const double	move_speed = 0.1;
	const double	rot_speed = 0.12;

	update_player(a, move_speed, rot_speed);
	render_frame(a);
	minimap_draw(a);
	mlx_put_image_to_window(a->mlx, a->win, a->frame.img, 0, 0);
	return (0);
}
