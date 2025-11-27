/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:48:00 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/27 10:32:54 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Count the number of wall cells ('1') in the map.
 *
 * @param cfg Pointer to the configuration containing the map.
 * @return Number of walls found.
 */
static int	count_walls(const t_config *cfg)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < cfg->map_h)
	{
		x = 0;
		while (x < cfg->map_w)
		{
			if (cfg->map[y][x] == '1')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/**
 * @brief Fill cfg->walls[] with the coordinates of all walls ('1') in the map.
 *
 * @param cfg Pointer to the configuration containing the map and walls array.
 */
static void	fill_walls(t_config *cfg)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	y = 0;
	while (y < cfg->map_h)
	{
		x = 0;
		while (x < cfg->map_w)
		{
			if (cfg->map[y][x] == '1')
				cfg->walls[i++] = (t_wall){x, y};
			x++;
		}
		y++;
	}
}

/**
 * @brief Allocate and fill the wall list (cfg->walls) for faster raycasting.
 *
 * Scans the normalized map to count all '1' cells, allocates
 * an array of t_wall with their coordinates, and fills it.
 *
 * @param cfg Pointer to the configuration structure.
 */
void	precompute_walls(t_config *cfg)
{
	cfg->n_walls = count_walls(cfg);
	cfg->walls = malloc(sizeof(t_wall) * cfg->n_walls);
	if (!cfg->walls)
	{
		free_config(cfg);
		error_exit("Error\nAlloc failure (walls)");
	}
	fill_walls(cfg);
}
