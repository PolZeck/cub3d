/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_closed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:52:00 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 18:52:59 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	check_map_closed(const t_config *cfg)
{
	if (!check_edges_closed(cfg))
		return (0);
	if (!check_interior_closed(cfg))
		return (0);
	return (1);
}
