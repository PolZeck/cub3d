/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:26:21 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:43:43 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"

/**
 * @brief Convert RGB values from config to 24-bit colors.
 *
 * Initializes ceiling and floor colors in the application structure
 * based on the RGB triplets provided in the configuration file.
 *
 * @param a   Pointer to the application context.
 * @param cfg Pointer to the loaded configuration data.
 */
static void	setup_colors(t_app *a, t_config *cfg)
{
	a->ceil_color = rgb24(cfg->ceiling.r, cfg->ceiling.g, cfg->ceiling.b);
	a->floor_color = rgb24(cfg->floor.r, cfg->floor.g, cfg->floor.b);
}

/**
 * @brief Apply orientation data to initialize the player's direction.
 *
 * Sets the player's direction and camera plane based on the provided
 * orientation structure, which defines both direction and FOV plane.
 *
 * @param a Pointer to the application context.
 * @param o Orientation structure (dir.x, dir.y, plane.x, plane.y).
 */
static void	apply_orient(t_app *a, t_orient o)
{
	a->pl.dir.x = o.dx;
	a->pl.dir.y = o.dy;
	a->pl.plane.x = o.px;
	a->pl.plane.y = o.py;
}

/**
 * @brief Determine initial player orientation from direction character.
 *
 * Sets player direction and camera plane vectors depending on whether
 * the player starts facing North, South, East, or West.
 *
 * @param a Pointer to the application context.
 * @param d Direction character ('N', 'S', 'E', or 'W').
 */
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

/**
 * @brief Initialize player position and facing direction from config.
 *
 * Converts player map coordinates to world-space coordinates (adding
 * 0.5 offset to center the player in a tile) and sets the correct
 * facing direction.
 *
 * @param a Pointer to the application context.
 */
void	init_player_from_cfg(t_app *a)
{
	a->pl.pos.x = a->cfg.player_x + 0.5;
	a->pl.pos.y = a->cfg.player_y + 0.5;
	set_dir_from_char(a, a->cfg.player_dir);
}

/**
 * @brief Main entry point for running the game application.
 *
 * Initializes the application structure, loads configuration, sets
 * up the MLX context, initializes the player and textures, and starts
 * the main rendering loop. This is the highest-level function called
 * after parsing the configuration file.
 *
 * @param cfg Pointer to the parsed configuration structure.
 * @return Always returns 0 (normal program termination).
 */
int	run_app(t_config *cfg)
{
	t_app	a;

	ft_bzero(&a, sizeof(a));
	a.mouse_warping = 0;
	a.mouse_sensi = 0.003;
	a.center_x = a.win_w / 2;
	a.center_y = a.win_h / 2;
	a.cfg = *cfg;
	a.win_w = 1024;
	a.win_h = 768;
	a.minimap.enabled = 1;
	a.minimap.tile = MINIMAP_TILE;
	a.minimap.w = MINIMAP_W;
	a.minimap.h = MINIMAP_HEIGHT;
	a.minimap.margin_x = MINIMAP_MARGIN_X;
	a.minimap.margin_y = MINIMAP_MARGIN_Y;
	setup_colors(&a, cfg);
	init_mlx_and_window(&a, cfg);
	init_player_from_cfg(&a);
	load_textures(&a);
	setup_hooks(&a);
	mlx_loop(a.mlx);
	return (0);
}
