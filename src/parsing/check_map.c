/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/10 17:25:21 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

static void	handle_player_char(t_config *cfg, int x, int y, int *players)
{
	cfg->player_x = x;
	cfg->player_y = y;
	cfg->player_dir = cfg->map[y][x];
	cfg->map[y][x] = '0';
	(*players)++;
}

static void	check_map_line(t_config *cfg, int y, int *players)
{
	int		x;
	char	c;

	x = 0;
	while (x < cfg->map_w)
	{
		c = cfg->map[y][x];
		if (!is_valid_map_char(c))
		{
			free_config(cfg);
			error_exit("Error\nInvalid char in map");
		}
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			handle_player_char(cfg, x, y, players);
		x++;
	}
}

int	check_map_chars_and_player(t_config *cfg)
{
	int	players;
	int	y;

	players = 0;
	y = 0;
	while (y < cfg->map_h)
	{
		check_map_line(cfg, y, &players);
		y++;
	}
	if (players != 1)
	{
		free_config(cfg);
		if (players == 0)
			error_exit("Error\nMissing player");
		else
			error_exit("Error\nMultiple players");
	}
	return (1);
}

int	validate_config(t_config *cfg)
{
	if (!check_map_chars_and_player(cfg))
		return (0);
	if (!check_map_closed(cfg))
	{
		free_config(cfg);
		error_exit("Error\nMap not closed");
	}
	return (1);
}
