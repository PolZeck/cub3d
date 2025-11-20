/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:26:42 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/20 15:41:34 by pledieu          ###   ########.fr       */
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

/**
 * @brief Allocates memory for the map rows in the configuration structure.
 * 
 * This function allocates space for `h + 1` pointers in `cfg->map`,
 * where the last element is reserved for a NULL terminator.
 * 
 * @param cfg Pointer to the configuration structure.
 * @param h Number of rows to allocate.
 * @return 1 if allocation succeeds, 0 otherwise.
 */
int	alloc_map_rows(t_config *cfg, int h)
{
	(void) h;
	cfg->map = malloc(sizeof(char *) * (h + 1));
	if (!cfg->map)
		return (0);
	return (1);
}

/**
 * @brief Cleans up partially allocated map rows on allocation failure.
 * 
 * This function frees all successfully allocated rows in `cfg->map`
 * up to the index `upto`, then frees the entire map and the original
 * raw data array to prevent memory leaks.
 * 
 * @param cfg Pointer to the configuration structure.
 * @param raw Pointer to the raw string array.
 * @param h Total height of the raw array.
 * @param upto Number of successfully allocated rows to free.
 */
static void	cleanup_alloc_fail(t_config *cfg, char **raw, int h, int upto)
{
	int	i;

	i = 0;
	while (i < upto)
		free(cfg->map[i++]);
	free(cfg->map);
	cfg->map = NULL;
	while (upto < h)
		free(raw[upto++]);
	free(raw);
}

/**
 * @brief Copies raw map rows into the configuration structure, 
 * handling allocation errors.
 * 
 * This function allocates memory for each row of the map in `cfg->map`,
 * copies and pads each line from the `raw` array using `copy_and_pad()`,
 * and frees the corresponding raw line. If any allocation fails, it
 * cleans up all allocated memory using `cleanup_alloc_fail()` and returns 0.
 * 
 * @param cfg Pointer to the configuration structure.
 * @param raw Array of raw map strings.
 * @param h Number of map rows.
 * @param w Maximum width of the map (used for padding).
 * @return 1 if copying succeeds, 0 otherwise.
 */
int	copy_rows_or_fail(t_config *cfg, char **raw, int h, int w)
{
	int	i;

	i = 0;
	while (i < h)
	{
		cfg->map[i] = malloc(w + 1);
		// if (i==3) cfg->map[i] = NULL;
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
