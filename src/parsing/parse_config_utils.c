/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:07:05 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:41:12 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Initializes a parsing state structure.
 * 
 * This function sets all members of the parsing state `t_pstate` to their
 * default values, preparing it for use in the configuration file parsing
 * process.
 * 
 * @param st Pointer to the parsing state structure to initialize.
 */
void	init_pstate(t_pstate *st)
{
	st->fd = -1;
	st->line = NULL;
	st->in_map = false;
	st->seen_blank_after_map = false;
	st->raw = NULL;
	st->n = 0;
	st->cap = 0;
}

/**
 * @brief Reads one line from the configuration file.
 * 
 * This function reads a single line from the file descriptor stored in
 * the parsing state using `get_next_line()`. The result is stored in
 * `st->line`.
 * 
 * @param st Pointer to the parsing state containing the file descriptor.
 * @return 1 if a line was successfully read,
 * 0 if end of file or an error occurred.
 */
int	read_one_line(t_pstate *st)
{
	st->line = get_next_line(st->fd);
	return (st->line != NULL);
}

/**
 * @brief Removes end-of-line characters from a string.
 * 
 * This function trims any trailing `'\n'` or `'\r'` characters from the end
 * of the provided string. The modification is done in place.
 * 
 * @param line String to process and strip of newline characters.
 */
void	strip_eol(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	while (len && (line[len - 1] == '\n' || line[len - 1] == '\r'))
	{
		len--;
		line[len] = '\0';
	}
}

/**
 * @brief Appends a line to the raw map data or exits on allocation failure.
 * 
 * This function adds a new line to the `raw` array of the parsing state.
 * If memory allocation fails during the process, it frees all relevant
 * resources and terminates the program with an error message.
 * 
 * @param st Pointer to the parsing state structure.
 * @param line Line to append to the raw map data.
 * @param cfg Pointer to the configuration structure for cleanup on error.
 */
void	append_or_die(t_pstate *st, char *line, t_config *cfg)
{
	if (parse_map_collect(&st->raw, &st->n, &st->cap, line))
		return ;
	close(st->fd);
	free(st->line);
	free(st->raw);
	free_config(cfg);
	error_exit("Error\nAlloc failure");
}

/**
 * @brief Processes a configuration line before the map section starts.
 * 
 * This function distinguishes between header lines and map lines:
 * 
 * - If the line is blank, it is ignored.
 * - If it matches a header type (`is_hdr`), it is parsed using `parse_hdr`.
 * - Otherwise, it is treated as the start of the map section.
 * 
 * Any error during header parsing results in cleanup and program termination.
 * 
 * @param cfg Pointer to the configuration structure being filled.
 * @param st Pointer to the parsing state structure.
 * @param is_hdr Function pointer that returns 1 if a line is a valid header.
 * @param parse_hdr Function pointer that parses a header line
 * into the configuration.
 */
void	before_map_step(t_config *cfg, t_pstate *st,
			int (*is_hdr)(const char *),
			int (*parse_hdr)(t_config *, const char *))
{
	char	*p;

	p = skip_spaces(st->line);
	if (*p == '\0')
	{
		free(st->line);
		return ;
	}
	if (is_hdr(p))
	{
		if (!parse_hdr(cfg, p))
		{
			free(st->line);
			free_config(cfg);
			close(st->fd);
			error_exit("Error\nInvalid header line");
		}
		free(st->line);
		return ;
	}
	st->in_map = true;
	append_or_die(st, st->line, cfg);
}
