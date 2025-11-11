/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:28 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:39:13 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Checks if a given character is valid for the map.
 * 
 * Valid map characters are '0', '1', 'N', 'S', 'E', 'W', and space (' ').
 * Any other character is considered invalid and will cause a parsing error.
 * 
 * @param c Character to validate.
 * @return 1 if the character is valid, 0 otherwise.
 */
static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
}

/**
 * @brief Handles detection of a player starting position in the map.
 * 
 * When a player character ('N', 'S', 'E', 'W') is found, this function
 * records its position and direction in the configuration, replaces it
 * with '0' in the map, and increments the player counter.
 * 
 * @param cfg Pointer to the configuration structure.
 * @param x X-coordinate of the player character.
 * @param y Y-coordinate of the player character.
 * @param players Pointer to the player count variable to increment.
 */
static void	handle_player_char(t_config *cfg, int x, int y, int *players)
{
	cfg->player_x = x;
	cfg->player_y = y;
	cfg->player_dir = cfg->map[y][x];
	cfg->map[y][x] = '0';
	(*players)++;
}

/**
 * @brief Checks all characters in a given map line 
 * for validity and player presence.
 * 
 * This function iterates through one row of the map 
 * and validates each character.
 * It also handles detection of player starting positions 
 * and ensures that only
 * one player is present in the map.
 * 
 * If an invalid character is found, the configuration is 
 * freed and the program exits.
 * 
 * @param cfg Pointer to the configuration structure containing the map.
 * @param y Index of the current map line being checked.
 * @param players Pointer to the player count variable.
 */
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

/**
 * @brief Validates all map characters and ensures there is exactly one player.
 * 
 * This function scans the entire map, validating each cell and counting player
 * starting positions. It ensures that there is exactly one player defined.
 * 
 * If no player or multiple players are found, the configuration is freed
 * and the program exits with an appropriate error message.
 * 
 * @param cfg Pointer to the configuration structure containing the map.
 * @return 1 if the map characters and player position are valid, 0 otherwise.
 */
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

/**
 * @brief Validates the configuration and the integrity of the map.
 * 
 * This is the main validation function called after parsing. It checks
 * that the map contains valid characters, exactly one player, and that
 * it is fully enclosed (no leaks). Any failure results in freeing the
 * configuration and exiting the program with an error message.
 * 
 * @param cfg Pointer to the configuration structure.
 * @return 1 if the configuration and map are valid, 0 otherwise.
 */
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
