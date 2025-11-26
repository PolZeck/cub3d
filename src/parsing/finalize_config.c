/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:04:14 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/26 14:45:59 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Removes trailing blank lines from the parsing state.
 * 
 * This function iterates backward through the raw map lines stored in
 * the parsing state and frees any trailing blank lines (as determined by
 * the provided `is_blank` function pointer). It stops once a non-blank line
 * is encountered.
 * 
 * @param st Pointer to the parsing state structure.
 * @param is_blank Function pointer that returns 1 if a line is blank, 
 * 0 otherwise.
 */
static void	trim_trailing_blank_lines(t_pstate *st,
			int (*is_blank)(const char *))
{
	while (st->n > 0 && is_blank(st->raw[st->n - 1]))
	{
		free(st->raw[st->n - 1]);
		st->n--;
	}
}

/**
 * @brief Performs the first stage of configuration finalization.
 * 
 * This stage verifies that all mandatory headers have been parsed,
 * ensures that a map section exists, and trims any blank lines at
 * the end of the map. It also handles error cases such as missing
 * headers or missing map data by freeing allocated structures and
 * exiting with an appropriate error message.
 * 
 * @param cfg Pointer to the configuration structure being built.
 * @param st Pointer to the parsing state structure.
 * @param is_blank Function pointer that checks whether a line is blank.
 */
static void	finalize_config_stage1(t_config *cfg, t_pstate *st,
			int (*is_blank)(const char *))
{
	close(st->fd);
	if (!st->in_map)
	{
		free_config(cfg);
		free_pstate(st);
		error_exit("Error\nMissing map at end of file");
	}
	if (!check_required_headers(cfg))
	{
		free_config(cfg);
		free_pstate(st);
		error_exit("Error\nMissing/duplicate headers");
	}
	trim_trailing_blank_lines(st, is_blank);
	if (st->n == 0)
	{
		free_config(cfg);
		free_pstate(st);
		error_exit("Error\nEmpty map");
	}
}

/**
 * @brief Performs the second stage of configuration finalization.
 * 
 * This stage normalizes the map to ensure consistent dimensions
 * and validates the resulting configuration. If either operation
 * fails, it frees the configuration and terminates the program
 * with an appropriate error message.
 * 
 * @param cfg Pointer to the configuration structure being validated.
 * @param st Pointer to the parsing state containing the raw map data.
 */
static void	finalize_config_stage2(t_config *cfg, t_pstate *st)
{
	if (!normalize_map(cfg, st->raw, st->n))
	{
		free_config(cfg);
		error_exit("Error\nMap normalization failed");
	}
	precompute_walls(cfg);
	if (!validate_config(cfg))
	{
		free_config(cfg);
		error_exit("Error\nInvalid configuration");
	}
}

/**
 * @brief Finalizes the configuration after parsing is complete.
 * 
 * This is the top-level function that finalizes the configuration by
 * performing two main stages:
 * 
 *  - Stage 1: Verifies headers, trims blank lines, and checks for map presence.
 *  - Stage 2: Normalizes the map and validates the configuration.
 * 
 * On any error, it frees allocated memory and terminates the program.
 * 
 * @param cfg Pointer to the configuration structure to finalize.
 * @param st Pointer to the parsing state structure.
 * @param is_blank Function pointer that checks whether a line is blank.
 */
void	finalize_config(t_config *cfg, t_pstate *st,
			int (*is_blank)(const char *))
{
	finalize_config_stage1(cfg, st, is_blank);
	finalize_config_stage2(cfg, st);
}
