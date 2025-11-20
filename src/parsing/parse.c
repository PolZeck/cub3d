/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:58:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/20 16:09:47 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Processes a line belonging to the map section during parsing.
 * 
 * This function handles each line after the map section has started.
 * - If the line is blank, it marks that a blank line was seen and stores it.
 * - If a non-empty line appears after a blank one, it triggers an error,
 *   since maps cannot contain non-contiguous sections.
 * - Otherwise, it simply appends the line to the raw map data.
 * 
 * @param cfg Pointer to the configuration structure.
 * @param st Pointer to the parsing state structure.
 */
void	in_map_step(t_config *cfg, t_pstate *st)
{
	char	*p;

	(void)cfg;
	p = skip_spaces(st->line);
	if (*p == '\0')
	{
		st->seen_blank_after_map = true;
		append_or_die(st, st->line, cfg);
		return ;
	}
	if (st->seen_blank_after_map)
	{
		free_pstate(st);
		free(st->line);
		free_config(cfg);
		error_exit("Error\nNon-empty line after map");
	}
	append_or_die(st, st->line, cfg);
}

/**
 * @brief Parses a header line defining a floor or ceiling color.
 *
 * This function checks whether the given pointer `ptr` refers to a
 * floor (`F`) or ceiling (`C`) color definition. It ensures that each
 * of these identifiers appears only once in the configuration file.
 *
 * - `"F"` → parses the floor RGB color  
 * - `"C"` → parses the ceiling RGB color  
 *
 * If a duplicate `F` or `C` line is encountered, the function returns 0
 * to indicate an invalid or already processed header.
 *
 * @param cfg Pointer to the configuration structure storing color data
 *            and flags (`seen_floor`, `seen_ceiling`).
 * @param ptr Pointer to the start of the header content (after trimming spaces).
 * @return 1 if a valid color line was parsed, 0 otherwise.
 */
int	parse_line_color(t_config *cfg, const char *ptr)
{
	if (!ft_strncmp(ptr, "F ", 2))
	{
		if (cfg->seen_floor)
			return (0);
		cfg->seen_floor = true;
		return (parse_color_line(&cfg->floor, ptr + 1));
	}
	if (!ft_strncmp(ptr, "C ", 2))
	{
		if (cfg->seen_ceiling)
			return (0);
		cfg->seen_ceiling = true;
		return (parse_color_line(&cfg->ceiling, ptr + 1));
	}
	return (0);
}

/**
 * @brief Parses a configuration header line and dispatches
 * 	it to the proper handler.
 *
 * This function identifies the type of header based on its prefix and
 * calls the corresponding parsing function. It supports:
 *
 * - `"NO"` → North texture  
 * - `"SO"` → South texture  
 * - `"WE"` → West texture  
 * - `"EA"` → East texture  
 * - `"F"` / `"C"` → Floor or ceiling color (delegated to `parse_line_color()`)  
 *
 * All texture identifiers must appear only once. Floor and ceiling
 * colors are validated by `parse_line_color()` which enforces the
 * single-occurrence rule.
 *
 * If the line does not match any known header format, the function
 * returns 0 to indicate an unrecognized or invalid header.
 *
 * @param cfg Pointer to the configuration structure.
 * @param line Raw line read from the configuration file.
 * @return 1 if the line corresponds to a valid header, 0 otherwise.
 */
int	parse_line_header(t_config *cfg, const char *line)
{
	const char	*ptr;

	ptr = skip_spaces(line);
	if (!ft_strncmp(ptr, "NO ", 3))
		return (parse_texture_line(&cfg->tx, "NO", ptr + 2));
	if (!ft_strncmp(ptr, "SO ", 3))
		return (parse_texture_line(&cfg->tx, "SO", ptr + 2));
	if (!ft_strncmp(ptr, "WE ", 3))
		return (parse_texture_line(&cfg->tx, "WE", ptr + 2));
	if (!ft_strncmp(ptr, "EA ", 3))
		return (parse_texture_line(&cfg->tx, "EA", ptr + 2));
	if (parse_line_color(cfg, ptr))
		return (1);
	return (0);
}

/**
 * @brief Parses an entire `.cub` configuration file.
 * 
 * This function orchestrates the parsing of a `.cub` configuration file.
 * It initializes parsing structures, opens the target file, and reads it
 * line by line. Depending on the parsing state, each line is processed as
 * either a header or a map entry.
 * 
 * Once the file has been fully read, the configuration is finalized with
 * `finalize_config()` to verify completeness and consistency.
 * 
 * On any error (e.g., missing headers, invalid map, allocation failure),
 * the function terminates execution with an error message.
 * 
 * @param path Path to the `.cub` configuration file.
 * @param cfg Pointer to the configuration structure to fill.
 * @return 1 if parsing succeeds, does not return on fatal errors.
 */
int	parse_config(const char *path, t_config *cfg)
{
	t_pstate	st;

	ft_bzero(cfg, sizeof(*cfg));
	init_pstate(&st);
	st.fd = open(path, O_RDONLY);
	if (st.fd < 0)
		error_exit("Error\nCannot open .cub");
	while (read_one_line(&st))
	{
		strip_eol(st.line);
		if (st.in_map)
			in_map_step(cfg, &st);
		else
			before_map_step(cfg, &st, is_header_line, parse_line_header);
	}
	close(st.fd);
	finalize_config(cfg, &st, is_only_spaces);
	return (1);
}
