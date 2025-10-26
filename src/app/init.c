/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:21 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 12:50:08 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

static void	setup_colors(t_app *a, t_config *cfg)
{
	a->ceil_color = rgb24(cfg->ceiling.r, cfg->ceiling.g, cfg->ceiling.b);
	a->floor_color = rgb24(cfg->floor.r, cfg->floor.g, cfg->floor.b);
}

static void	apply_orient(t_app *a, t_orient o)
{
	a->pl.dir_x = o.dx;
	a->pl.dir_y = o.dy;
	a->pl.plane_x = o.px;
	a->pl.plane_y = o.py;
}

static void	set_dir_from_char(t_app *a, char d)
{
	t_orient	o;

	if (d == 'N')
		o = (t_orient){0.0, -1.0, 0.66, 0.0};
	else if (d == 'S')
		o = (t_orient){0.0, 1.0, -0.66, 0.0};
	else if (d == 'E')
		o = (t_orient){1.0, 0.0, 0.0, 0.66};
	else
		o = (t_orient){-1.0, 0.0, 0.0, -0.66};
	apply_orient(a, o);
}

void	init_player_from_cfg(t_app *a)
{
	a->pl.pos_x = a->cfg.player_x + 0.5;
	a->pl.pos_y = a->cfg.player_y + 0.5;
	set_dir_from_char(a, a->cfg.player_dir);
}

int	run_app(t_config *cfg)
{
	t_app	a;

	ft_bzero(&a, sizeof(a));
	a.cfg = *cfg;
	a.win_w = 1024;
	a.win_h = 768;
	setup_colors(&a, cfg);
	init_mlx_and_window(&a);
	init_player_from_cfg(&a);
	load_textures(&a);
	setup_hooks(&a);
	mlx_loop(a.mlx);
	return (0);
}
