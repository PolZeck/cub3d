/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:09 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/12 08:16:22 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

/**
 * @brief Render a full frame using the raycasting pipeline.
 *
 * This function performs one complete rendering pass of the 3D scene.
 * It first fills the background (ceiling and floor), then iterates over
 * each vertical screen column. For each column, it initializes a ray,
 * computes intersections, determines wall height, selects the texture,
 * and draws the textured column to the frame buffer.
 *
 * @param a Pointer to the application context (contains player, map,
 *          textures, and frame buffer).
 * @return Always returns 0 (required by MLX loop hook convention).
 */
int	render_frame(t_app *a)
{
	int		x;
	t_ray	r;

	fill_half_screens(a);
	x = 0;
	while (x < a->frame.w)
	{
		ray_init(a, &r, x);
		ray_find_first_hit(a, &r);
		ray_post(a, &r);
		draw_tex_column(a, x, &r);
		x++;
	}
	return (0);
}
