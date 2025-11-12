/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:50:56 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/12 08:11:07 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include "cub3d.h"
# include "mlx.h"
# include <math.h>
# include "vec2.h"

typedef struct s_app	t_app;
typedef struct s_img	t_img;
typedef struct s_vline	t_vline;
typedef struct s_ray	t_ray;

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
	const t_img	*tex;
	int			tex_x;
	int			side;
	double		step;
}	t_drawctx;

typedef struct s_slabs
{
	double	minx;
	double	maxx;
	double	miny;
	double	maxy;
	double	invx;
	double	invy;
}	t_slabs;

typedef struct s_axis_in
{
	double	minv;
	double	maxv;
	double	ro;
	double	inv;
}	t_axis_in;

typedef struct s_axis_out
{
	double	tmin;
	double	tmax;
}	t_axis_out;

typedef struct s_hit_in
{
	double	tminx;
	double	tminy;
	double	tmaxx;
	double	tmaxy;
}	t_hit_in;

typedef struct s_hit_out
{
	double	t_enter;
	int		side;
}	t_hit_out;

typedef struct s_ray_box_query
{
	t_v2	ro;
	t_v2	rd;
	int		bx;
	int		by;
}	t_ray_box_query;

typedef struct s_ray_box_hit
{
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

void			ray_find_first_hit(t_app *a, t_ray *r);
void			ray_post(t_app *a, t_ray *r);
int				column_color(t_ray *r);
void			ray_init(t_app *a, t_ray *r, int x);
int				render_frame(t_app *a);
void			draw_tex_column(t_app *a, int x, const t_ray *r);
int				ray_box_intersect(const t_ray_box_query *q, t_ray_box_hit *hit);
int				map_w(const t_app *a);
int				map_h(const t_app *a);
char			map_at(const t_app *a, int y, int x);
const t_img		*get_tex(t_app *a, const t_ray *r);

#endif