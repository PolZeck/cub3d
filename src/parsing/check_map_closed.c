/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:52:00 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:39:35 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if all neighboring cells of a given map position are closed.
 * 
 * This function verifies that the four adjacent tiles (up, down, left, right)
 * around the given coordinate `(x, y)` are not empty and within the map bounds.
 * It ensures that an open tile ('0') is not adjacent to an empty space (' '),
 * preventing leaks in the map layout.
 * 
 * @param cfg Pointer to the configuration structure containing the map data.
 * @param x X-coordinate of the cell to check.
 * @param y Y-coordinate of the cell to check.
 * @return 1 if all neighbors are valid and closed, 0 otherwise.
 */
static int	check_neighbors_are_closed(const t_config *cfg, int x, int y)
{
	const int	dx[4] = {1, -1, 0, 0};
	const int	dy[4] = {0, 0, 1, -1};
	int			k;
	int			nx;
	int			ny;

	k = 0;
	while (k < 4)
	{
		nx = x + dx[k];
		ny = y + dy[k];
		if (nx < 0 || ny < 0 || nx >= cfg->map_w || ny >= cfg->map_h)
			return (0);
		if (cfg->map[ny][nx] == ' ')
			return (0);
		k++;
	}
	return (1);
}

/**
 * @brief Checks that the map edges are properly closed.
 * 
 * This function ensures that the outermost rows and columns of the map
 * do not contain any open space ('0'). Only walls ('1') and spaces outside
 * the playable area are allowed on the borders.
 * 
 * @param cfg Pointer to the configuration structure containing the map data.
 * @return 1 if all map edges are closed, 0 otherwise.
 */
static int	check_edges_closed(const t_config *cfg)
{
	int	x;
	int	y;

	x = 0;
	while (x < cfg->map_w)
	{
		if (cfg->map[0][x] == '0'
			|| cfg->map[cfg->map_h - 1][x] == '0')
			return (0);
		x++;
	}
	y = 0;
	while (y < cfg->map_h)
	{
		if (cfg->map[y][0] == '0'
			|| cfg->map[y][cfg->map_w - 1] == '0')
			return (0);
		y++;
	}
	return (1);
}

/**
 * @brief Checks that all interior open cells are surrounded by valid tiles.
 * 
 * This function iterates over the entire map and for every open space ('0'),
 * it checks that all four adjacent cells are valid (not empty or out of bounds)
 * using `check_neighbors_are_closed()`. 
 * This ensures that the interior of the map is fully enclosed.
 * 
 * @param cfg Pointer to the configuration structure containing the map data.
 * @return 1 if all interior cells are properly closed, 0 otherwise.
 */
static int	check_interior_closed(const t_config *cfg)
{
	int	y;
	int	x;

	y = 0;
	while (y < cfg->map_h)
	{
		x = 0;
		while (x < cfg->map_w)
		{
			if (cfg->map[y][x] == '0')
			{
				if (!check_neighbors_are_closed(cfg, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

/**
 * @brief Validates that the map is completely enclosed.
 * 
 * This is the main function that verifies the integrity of the map layout.
 * It ensures both the map edges and the interior spaces are properly closed,
 * preventing leaks or invalid playable areas.
 * 
 * @param cfg Pointer to the configuration structure containing the map data.
 * @return 1 if the entire map is closed, 0 otherwise.
 */
int	check_map_closed(const t_config *cfg)
{
	if (!check_edges_closed(cfg))
		return (0);
	if (!check_interior_closed(cfg))
		return (0);
	return (1);
}
