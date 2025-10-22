/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:58:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 09:21:08 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char *skip_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t') s++;
	return (char *)s;
}

static int is_only_spaces(const char *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\r') s++;
	return (*s == '\0');
}

static int	is_header_line(const char *line)
{
	line = skip_spaces(line);
	return (!ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3)
		|| !ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3)
		|| !ft_strncmp(line, "F ", 2)  || !ft_strncmp(line, "C ", 2));
}

int	parse_line_header(t_config *cfg, const char *line)
{
	const char	*ptr = skip_spaces(line);

	if (!ft_strncmp(ptr, "NO ", 3))
		return parse_texture_line(&cfg->tx, "NO", ptr + 2);
	if (!ft_strncmp(ptr, "SO ", 3))
		return parse_texture_line(&cfg->tx, "SO", ptr + 2);
	if (!ft_strncmp(ptr, "WE ", 3))
		return parse_texture_line(&cfg->tx, "WE", ptr + 2);
	if (!ft_strncmp(ptr, "EA ", 3))
		return parse_texture_line(&cfg->tx, "EA", ptr + 2);
	if (!ft_strncmp(ptr, "F ", 2))
		return parse_color_line(&cfg->floor, ptr + 1);
	if (!ft_strncmp(ptr, "C ", 2))
		return parse_color_line(&cfg->ceiling, ptr + 1);
	return (0);
}

int parse_config(const char *path, t_config *cfg)
{
    int   fd;
    char *line;
    bool  in_map = false;              // <= une seule fois
    bool  seen_blank_after_map = false;
    char **raw_lines = NULL;
    int   n = 0, cap = 0;

    ft_bzero(cfg, sizeof(*cfg));
    fd = open(path, O_RDONLY);
    if (fd < 0)
        error_exit("Error\nCannot open .cub");

    while ((line = get_next_line(fd)))
    {
        // strip \n et \r (CRLF)
        size_t len = ft_strlen(line);
        while (len && (line[len - 1] == '\n' || line[len - 1] == '\r'))
            line[--len] = '\0';

        if (!in_map) {
            char *p = skip_spaces(line);
            if (*p == '\0') { free(line); continue; } // lignes vides OK avant la map
            if (is_header_line(p)) {
                if (!parse_line_header(cfg, p)) {
                    free(line); close(fd);
                    error_exit("Error\nInvalid header line");
                }
                free(line);
            } else {
                // début de map
                in_map = true;
                if (!parse_map_collect(&raw_lines, &n, &cap, line)) {
                    close(fd); error_exit("Error\nAlloc failure");
                }
            }
        } else {
            char *p = skip_spaces(line);
            if (*p == '\0') {
                // blanc après avoir commencé la map : marquer fin de map
                seen_blank_after_map = true;
                if (!parse_map_collect(&raw_lines, &n, &cap, line)) {
                    close(fd); error_exit("Error\nAlloc failure");
                }
                continue;
            }
            if (seen_blank_after_map) {
                free(line); close(fd);
                error_exit("Error\nNon-empty line after map");
            }
            if (!parse_map_collect(&raw_lines, &n, &cap, line)) {
                close(fd); error_exit("Error\nAlloc failure");
            }
        }
    }
    close(fd);

    if (!in_map)
        error_exit("Error\nMissing map at end of file");
    if (!check_required_headers(cfg))
        error_exit("Error\nMissing/duplicate headers");
    while (n > 0 && is_only_spaces(raw_lines[n - 1])) {
        free(raw_lines[n - 1]);
        n--;
    }
    if (n == 0)
        error_exit("Error\nEmpty map");
    // 🔺🔺🔺 FIN DU BLOC À INSÉRER 🔺🔺🔺

    if (!normalize_map(cfg, raw_lines, n))
        error_exit("Error\nMap normalization failed");

    if (!validate_config(cfg))
        error_exit("Error\nInvalid configuration");

    return (1);
}