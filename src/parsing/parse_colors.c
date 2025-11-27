/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:56:29 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/27 15:54:43 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Parses an RGB triplet "R,G,B" into a t_rgb structure.
 *
 * This function duplicates the string, validates comma count,
 * delegates splitting + integer extraction, and fills the output struct.
 *
 * @param s Input string containing an RGB triplet.
 * @param out Pointer to the resulting t_rgb.
 * @return 1 if parsing succeeds, 0 otherwise.
 */
static int	parse_rgb_triplet(const char *s, t_rgb *out)
{
	char	*mutable;
	int		vals[3];

	mutable = ft_strdup(s);
	if (!mutable)
		return (0);
	if (!check_coma(mutable))
	{
		free(mutable);
		return (0);
	}
	if (!extract_rgb_values(mutable, vals))
	{
		free(mutable);
		return (0);
	}
	free(mutable);
	out->r = vals[0];
	out->g = vals[1];
	out->b = vals[2];
	return (1);
}

/**
 * @brief Parses a line defining a color in the configuration file.
 * 
 * This function skips the first character (usually 'F' or 'C'), trims
 * leading whitespace, and delegates the actual RGB parsing to
 * `parse_rgb_triplet()`. It also initializes the output color values
 * to -1 before parsing.
 * 
 * Example of a valid input line:
 * ```
 * F 220,100,0
 * ```
 * 
 * @param out Pointer to the RGB structure to fill with parsed values.
 * @param rest Pointer to the string containing the rest of the line
 * after the identifier.
 * @return 1 if parsing succeeds, 0 otherwise.
 */
int	parse_color_line(t_rgb *out, const char *rest)
{
	char	*p;

	p = (char *)rest;
	if (*p == '\0')
		return (0);
	p++;
	while (*p == ' ' || *p == '\t')
		p++;
	if (!*p)
		return (0);
	out->r = -1;
	out->g = -1;
	out->b = -1;
	return (parse_rgb_triplet(p, out));
}
