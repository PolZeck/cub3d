/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_config.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:04:14 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 11:07:48 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	trim_trailing_blank_lines(t_pstate *st,
			int (*is_blank)(const char *))
{
	while (st->n > 0 && is_blank(st->raw[st->n - 1]))
	{
		free(st->raw[st->n - 1]);
		st->n--;
	}
}

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

static void	finalize_config_stage2(t_config *cfg, t_pstate *st)
{
	if (!normalize_map(cfg, st->raw, st->n))
	{
		free_config(cfg);
		error_exit("Error\nMap normalization failed");
	}
	if (!validate_config(cfg))
	{
		free_config(cfg);
		error_exit("Error\nInvalid configuration");
	}
}

void	finalize_config(t_config *cfg, t_pstate *st,
			int (*is_blank)(const char *))
{
	finalize_config_stage1(cfg, st, is_blank);
	finalize_config_stage2(cfg, st);
}
