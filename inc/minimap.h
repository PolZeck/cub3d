/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 14:33:12 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 14:55:27 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIMAP_H
# define MINIMAP_H

# include "cub3d.h"

# define MINIMAP_TILE 8
# define MINIMAP_W 200
# define MINIMAP_HEIGHT 200
# define MINIMAP_MARGIN_X 10
# define MINIMAP_MARGIN_Y 10

typedef struct s_app	t_app ;
typedef struct s_img	t_img ;

typedef struct s_minimap
{
	int	enabled;
	int	tile;
	int	w;
	int	h;
	int	margin_x;
	int	margin_y;
}	t_minimap;

typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
	int	color;
}	t_rect;

typedef struct s_mmctx
{
	int	offx;
	int	offy;
	int	tile;
	int	vis_w;
	int	vis_h;
	int	rad_x;
	int	rad_y;
	int	cx;
	int	cy;
}	t_mmctx;

void	minimap_draw(t_app *a);
void	fill_rect(t_img *img, t_rect r);
int		color_for_cell(char c);
void	minimap_draw_row(t_app *a, t_mmctx *c, int y, int dest_y);
void	mmctx_init(t_app *a, t_mmctx *c, int offx, int offy);

#endif