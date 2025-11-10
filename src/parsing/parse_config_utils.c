/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:07:05 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/10 17:24:06 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	read_one_line(t_pstate *st)
{
	st->line = get_next_line(st->fd);
	return (st->line != NULL);
}

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

void	append_or_die(t_pstate *st, char *line)
{
	if (!parse_map_collect(&st->raw, &st->n, &st->cap, line))
	{
		close(st->fd);
		error_exit("Error\nAlloc failure");
	}
}

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
			close(st->fd);
			error_exit("Error\nInvalid header line");
		}
		free(st->line);
		return ;
	}
	st->in_map = true;
	append_or_die(st, st->line);
}
