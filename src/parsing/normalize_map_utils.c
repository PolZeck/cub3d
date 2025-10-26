/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:26:42 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 18:38:54 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	copy_and_pad(char *dst, const char *src, int w)
{
	int	i;

	i = 0;
	while (src[i] && i < w)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < w)
		dst[i++] = ' ';
	dst[i] = '\0';
	return (1);
}

void	free_raw_vec(char **raw, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free(raw[i]);
		i++;
	}
	free(raw);
}

int	alloc_map_rows(t_config *cfg, int h)
{
	cfg->map = malloc(sizeof(char *) * (h + 1));
	if (!cfg->map)
		return (0);
	return (1);
}

static void	cleanup_alloc_fail(t_config *cfg, char **raw, int h, int upto)
{
	int	i;

	i = 0;
	while (i < upto)
	{
		free(cfg->map[i]);
		i++;
	}
	free(cfg->map);
	free_raw_vec(raw, h);
}

int	copy_rows_or_fail(t_config *cfg, char **raw, int h, int w)
{
	int	i;

	i = 0;
	while (i < h)
	{
		cfg->map[i] = malloc(w + 1);
		if (!cfg->map[i])
		{
			cleanup_alloc_fail(cfg, raw, h, i);
			return (0);
		}
		copy_and_pad(cfg->map[i], raw[i], w);
		free(raw[i]);
		i++;
	}
	cfg->map[h] = NULL;
	free(raw);
	return (1);
}
