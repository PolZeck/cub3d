/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 11:23:03 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 11:31:50 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

void	dda_run(t_app *a, t_ray *r)
{
	while (!r->hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (r->map_x < 0 || r->map_y < 0
			|| r->map_x >= a->cfg.map_w || r->map_y >= a->cfg.map_h)
			r->hit = 1;
		else if (a->cfg.map[r->map_y][r->map_x] == '1')
			r->hit = 1;
	}
}
