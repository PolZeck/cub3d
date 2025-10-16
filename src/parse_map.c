/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:00 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/15 14:19:22 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_map_collect(char ***vec, int *n, int *cap, char *line)
{
	if (*cap == 0)
	{
		*cap = 16;
		*vec = malloc(sizeof(char*) * (*cap));
		if (!*vec)
		{
			free(line);
			return 0;
		}
	}
	if (*n >= *cap)
	{
		int newcap = (*cap) * 2;
		char **tmp = malloc(sizeof(char*) * newcap);
		if (!tmp) { free(line); return 0; }
		for (int i = 0; i < *n; ++i) tmp[i] = (*vec)[i];
		free(*vec);
		*vec = tmp;
		*cap = newcap;
	}
	(*vec)[*n] = line;
	(*n)++;
	return (1);
}

static int copy_and_pad(char *dst, const char *src, int w)
{
	int i = 0;
	while (src[i] && i < w)
	{
		if (src[i] == ' ' || src[i] == '\t')
			error_exit("Error\nSpaces not allowed in map");
		dst[i] = src[i];
		i++;
	}
	while (i < w)
		dst[i++] = '1';   // pad en '1' pour fermer la carte
	dst[i] = '\0';
	return (1);
}



int	normalize_map(t_config *cfg, char **raw, int n)
{
	int h = n;
	int w = 0;

	for (int i = 0; i < h; ++i)
		w = ft_max(w, (int)ft_strlen(raw[i]));

	cfg->map = malloc(sizeof(char *) * (h + 1));
	if (!cfg->map) { for (int i=0;i<h;++i) free(raw[i]); free(raw); return 0; }
	for (int i = 0; i < h; ++i)
	{
		cfg->map[i] = malloc(w + 1);
		if (!cfg->map[i])
		{
			for (int k=0;k<i;++k) free(cfg->map[k]);
			free(cfg->map);
			for (int k=0;k<h;++k) free(raw[k]);
			free(raw);
			return (0);
		}
		copy_and_pad(cfg->map[i], raw[i], w);
		free(raw[i]);
	}
	cfg->map[h] = NULL;
	free(raw);
	cfg->map_h = h;
	cfg->map_w = w;
	return (1);
}
