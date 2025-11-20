/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:00:00 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/20 16:01:24 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Expands a dynamically allocated array of strings
 * when capacity is reached.
 * 
 * This function doubles the current capacity of a dynamically allocated
 * string array (`vec`). It allocates a new larger array, copies the existing
 * elements into it, frees the old array, and updates the capacity value.
 * 
 * If allocation fails, it frees the current `line` and returns 0.
 * 
 * @param vec Pointer to the array of strings to expand.
 * @param cap Pointer to the current capacity value (will be updated).
 * @param n Current number of elements in the array.
 * @param line Line to free in case of allocation failure.
 * @return 1 if the expansion succeeds, 0 otherwise.
 */
static int	expand_vec(char ***vec, int *cap, int n, char *line)
{
	int		newcap;
	char	**tmp;
	int		i;

	(void)line;
	newcap = (*cap) * 2;
	tmp = malloc(sizeof(char *) * newcap);
	if (!tmp)
		return (0);
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

/**
 * @brief Appends a line to a dynamic vector of map strings.
 * 
 * This function ensures that there is enough space in the array to append
 * the new line. 
 * If necessary, it expands the capacity using `expand_vec()`.
 * The new line is stored at the end of the array,
 * and the count `n` is incremented.
 * 
 * @param vec Pointer to the array of strings (will be allocated or reallocated).
 * @param n Pointer to the current number of elements in the array.
 * @param cap Pointer to the current capacity value.
 * @param line Line to append to the array.
 * @return 1 if the line was successfully added, 0 otherwise.
 */
int	parse_map_collect(char ***vec, int *n, int *cap, char *line)
{
	if (*cap == 0)
	{
		*cap = 16;
		*vec = malloc(sizeof(char *) * (*cap));
		if (!*vec)
			return (0);
	}
	if (*n >= *cap && !expand_vec(vec, cap, *n, line))
		return (0);
	(*vec)[*n] = line;
	(*n)++;
	return (1);
}

/**
 * @brief Normalizes the raw map lines into a rectangular 2D map array.
 * 
 * This function computes the map height and width, allocates a properly sized
 * 2D array (`cfg->map`), and copies each line from the raw input,
 * padding shorter lines with spaces to ensure consistent width. 
 * The dimensions are stored in `cfg->map_h` and `cfg->map_w`.
 * 
 * @param cfg Pointer to the configuration structure where the map is stored.
 * @param raw Array of raw map strings read from the file.
 * @param n Number of map lines in the `raw` array.
 * @return 1 if normalization succeeds, 0 otherwise.
 */
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
	{
		return (0);
	}
	cfg->map_h = h;
	cfg->map_w = w;
	return (1);
}
