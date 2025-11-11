/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:00 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 11:21:22 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	expand_vec(char ***vec, int *cap, int n, char *line)
{
	int		newcap;
	char	**tmp;
	int		i;

	newcap = (*cap) * 2;
	tmp = malloc(sizeof(char *) * newcap);
	if (!tmp)
	{
		free(line);
		return (0);
	}
	i = 0;
	while (i < n)
	{
		tmp[i] = (*vec)[i];
		i++;
	}
	free(*vec);
	*vec = tmp;
	*cap = newcap;
	return (1);
}

int	parse_map_collect(char ***vec, int *n, int *cap, char *line)
{
	if (*cap == 0)
	{
		*cap = 16;
		*vec = malloc(sizeof(char *) * (*cap));
		if (!*vec)
		{
			free(line);
			return (0);
		}
	}
	if (*n >= *cap && !expand_vec(vec, cap, *n, line))
		return (0);
	(*vec)[*n] = line;
	(*n)++;
	return (1);
}

int	normalize_map(t_config *cfg, char **raw, int n)
{
	int	h;
	int	w;
	int	i;

	h = n;
	w = 0;
	i = 0;
	while (i < h)
	{
		w = ft_max(w, (int)ft_strlen(raw[i]));
		i++;
	}
	if (!alloc_map_rows(cfg, h))
	{
		free_raw_vec(raw, h);
		return (0);
	}
	if (!copy_rows_or_fail(cfg, raw, h, w))
		return (0);
	cfg->map_h = h;
	cfg->map_w = w;
	return (1);
}
