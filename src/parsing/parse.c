/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:58:34 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 18:13:05 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	in_map_step(t_config *cfg, t_pstate *st)
{
	char	*p;

	(void)cfg;
	p = skip_spaces(st->line);
	if (*p == '\0')
	{
		st->seen_blank_after_map = true;
		append_or_die(st, st->line);
		return ;
	}
	if (st->seen_blank_after_map)
	{
		free(st->line);
		close(st->fd);
		error_exit("Error\nNon-empty line after map");
	}
	append_or_die(st, st->line);
}

static void	trim_trailing_blank_lines(t_pstate *st,
			int (*is_blank)(const char *))
{
	while (st->n > 0 && is_blank(st->raw[st->n - 1]))
	{
		free(st->raw[st->n - 1]);
		st->n--;
	}
}

void	finalize_config(t_config *cfg, t_pstate *st,
			int (*is_blank)(const char *))
{
	close(st->fd);
	if (!st->in_map)
		error_exit("Error\nMissing map at end of file");
	if (!check_required_headers(cfg))
		error_exit("Error\nMissing/duplicate headers");
	trim_trailing_blank_lines(st, is_blank);
	if (st->n == 0)
		error_exit("Error\nEmpty map");
	if (!normalize_map(cfg, st->raw, st->n))
		error_exit("Error\nMap normalization failed");
	if (!validate_config(cfg))
		error_exit("Error\nInvalid configuration");
}


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
	if (!ft_strncmp(ptr, "F ", 2))
		return (parse_color_line(&cfg->floor, ptr + 1));
	if (!ft_strncmp(ptr, "C ", 2))
		return (parse_color_line(&cfg->ceiling, ptr + 1));
	return (0);
}

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
