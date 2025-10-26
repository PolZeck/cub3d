/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:09 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 13:18:41 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		dda_init(a, &r);
		dda_run(a, &r);
		ray_post(a, &r);
		draw_tex_column(a, x, &r);
		x++;
	}
	return (0);
}
