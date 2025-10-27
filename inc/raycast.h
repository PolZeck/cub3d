/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:50:56 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/27 11:10:24 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "cub3d.h"
#include "mlx.h"
#include <math.h>
#include "vec2.h"

typedef struct s_app   t_app;
typedef struct s_img   t_img;
typedef struct s_vline t_vline;
typedef struct s_ray   t_ray;


#define pos_x		pos.x
#define pos_y		pos.y
#define dir_x		dir.x
#define dir_y		dir.y
#define plane_x		plane.x
#define plane_y		plane.y
#define ray_dir_x	ray_dir.x
#define ray_dir_y	ray_dir.y
#define delta_x		delta.x
#define delta_y		delta.y
#define side_x		sdist.x
#define side_y		sdist.y
/* ------------------------------------------------------------------- */

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
    double       step;
}   t_drawctx;

typedef struct s_slabs
{
	double	minx;
	double	maxx;
	double	miny;
	double	maxy;
	double	invx;
	double	invy;
}	t_slabs;

typedef struct s_axis_in {
	double	minv, maxv, ro, inv;
}	t_axis_in;

typedef struct s_axis_out {
	double	tmin, tmax;
}	t_axis_out;

typedef struct s_hit_in {
	double	tminx, tminy, tmaxx, tmaxy;
}	t_hit_in;

typedef struct s_hit_out {
	double	t_enter;
	int		side;
}	t_hit_out;

typedef struct s_ray_box_query {
	t_v2	ro;
	t_v2	rd;
	int		bx;
	int		by;
}	t_ray_box_query;

typedef struct s_ray_box_hit {
	double	t_enter;
	int		side;
}	t_ray_box_hit;

typedef struct s_hit_update
{
	double	t;
	int		x;
	int		y;
	int		side;
}	t_hit_update;

#define MAP_W(A)        ((A)->cfg.map_w)
#define MAP_H(A)        ((A)->cfg.map_h)
#define MAP_AT(A,Y,X)   ((A)->cfg.map[(Y)][(X)])

int		render_frame(t_app *a);
void	ray_find_first_hit(t_app *a, t_ray *r);
void	ray_post(t_app *a, t_ray *r);
int		column_color(t_ray *r);
void	ray_prepare_intersection(t_app *a, t_ray *r);
void	ray_init(t_app *a, t_ray *r, int x);
int		render_frame(t_app *a);
// t_face	pick_face(int side, double ray_dir_x, double ray_dir_y);
void	draw_tex_column(t_app *a, int x, const t_ray *r);
const t_img	*get_tex(t_app *a, const t_ray *r);
int	ray_box_intersect(const t_ray_box_query *q, t_ray_box_hit *hit);


#endif