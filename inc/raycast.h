/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:50:56 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 13:40:30 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "cub3d.h"
#include "runtime.h"
#include "mlx.h"
#include <math.h>

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_dist;
	int		line_h;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_vline
{
	int	x;
	int	y0;
	int	y1;
	int	color;
}	t_vline;

typedef struct s_span
{
	int		y0;
	int		y1;
	double	tex_pos;
}	t_span;

typedef struct s_drawctx
{
    const t_img *tex;
    int          tex_x;
    int          side;
    double       step;   /* <-- AJOUT */
}   t_drawctx;

void	draw_vline(t_img *img, t_vline v);
int		render_frame(t_app *a);
void	dda_run(t_app *a, t_ray *r);
void	ray_post(t_app *a, t_ray *r);
int		column_color(t_ray *r);
void	dda_init(t_app *a, t_ray *r);
void	ray_init(t_app *a, t_ray *r, int x);
int		render_frame(t_app *a);
// t_face	pick_face(int side, double ray_dir_x, double ray_dir_y);
void	draw_tex_column(t_app *a, int x, const t_ray *r);
const t_img	*get_tex(t_app *a, const t_ray *r);

#endif