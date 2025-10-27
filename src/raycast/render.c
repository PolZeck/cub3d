/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:09 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 10:24:29 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

int	render_frame(t_app *a)
{
	int		x;
	t_ray	r;

	fill_half_screens(a);
	x = 0;
	while (x < a->frame.w)
	{
		ray_init(a, &r, x);
		ray_prepare_intersection(a, &r);
		ray_find_first_hit(a, &r);
		ray_post(a, &r);
		draw_tex_column(a, x, &r);
		x++;
	}
	return (0);
}
