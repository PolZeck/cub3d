/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/15 14:18:53 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' ||
			c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	check_map_chars_and_player(t_config *cfg)
{
	int players = 0;

	for (int y = 0; y < cfg->map_h; ++y)
	for (int x = 0; x < cfg->map_w; ++x)
	{
		char c = cfg->map[y][x];
		if (!is_valid_map_char(c))
			error_exit("Error\nInvalid char in map");
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			cfg->player_x = x;
			cfg->player_y = y;
			cfg->player_dir = c;
			cfg->map[y][x] = '0'; // simplifie les checks
			players++;
		}
	}
	if (players != 1)
		error_exit(players == 0 ? "Error\nMissing player" : "Error\nMultiple players");
	return (1);
}

// interdit que des cases navigables touchent l'extérieur ou des espaces
static int	check_neighbors_are_closed(const t_config *cfg, int x, int y)
{
	const int dx[4] = {1, -1, 0, 0};
	const int dy[4] = {0, 0, 1, -1};

	for (int k = 0; k < 4; ++k)
	{
		int nx = x + dx[k];
		int ny = y + dy[k];
		if (nx < 0 || ny < 0 || nx >= cfg->map_w || ny >= cfg->map_h)
			return (0);
		if (cfg->map[ny][nx] == ' ')
			return (0);
	}
	return (1);
}

int	check_map_closed(const t_config *cfg)
{
	// bords : aucune case '0' ne doit toucher le bord ou un espace
	for (int x = 0; x < cfg->map_w; ++x)
	{
		if (cfg->map[0][x] == '0' || cfg->map[cfg->map_h-1][x] == '0')
			return (0);
	}
	for (int y = 0; y < cfg->map_h; ++y)
	{
		if (cfg->map[y][0] == '0' || cfg->map[y][cfg->map_w-1] == '0')
			return (0);
	}
	// voisinage
	for (int y = 0; y < cfg->map_h; ++y)
	for (int x = 0; x < cfg->map_w; ++x)
	{
		if (cfg->map[y][x] == '0')
		{
			if (!check_neighbors_are_closed(cfg, x, y))
				return (0);
		}
	}
	return (1);
}

int	validate_config(t_config *cfg)
{
	if (!check_map_chars_and_player(cfg))
		return (0);
	if (!check_map_closed(cfg))
		error_exit("Error\nMap not closed");
	return (1);
}
