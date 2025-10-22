/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:09 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 11:29:32 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

int	render_frame(t_app *a)
{
	int		x;
	t_ray	r;
	int		color;
	t_vline	v;

	fill_half_screens(a);
	x = 0;
	while (x < a->frame.w)
	{
		ray_init(a, &r, x);
		dda_init(a, &r);
		dda_run(a, &r);
		ray_post(a, &r);
		color = column_color(&r);
		v.x = x;
		v.y0 = r.draw_start;
		v.y1 = r.draw_end;
		v.color = color;
		draw_vline(&a->frame, v);
		x++;
	}
	return (0);
}
