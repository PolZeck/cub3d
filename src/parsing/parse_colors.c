/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:56:29 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:40:46 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Trims leading and trailing spaces and tabs from a string.
 * 
 * This function returns a pointer to the first non-space and non-tab character
 * of the string `s`, and replaces the last trailing whitespace 
 * with a null terminator.
 * The returned pointer may be different from the original string if it starts
 * with spaces or tabs.
 * 
 * @param s String to trim (modified in place).
 * @return Pointer to the trimmed string (may not be the original pointer).
 */
static char	*strtrim_spaces(char *s)
{
	char	*start;
	char	*end;

	start = s;
	while (*start == ' ' || *start == '\t')
		start++;
	if (*start == '\0')
		return (start);
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t'))
		end--;
	*(end + 1) = '\0';
	return (start);
}

/**
 * @brief Validates and converts a trimmed string to an integer RGB value.
 * 
 * This function ensures that the provided string `trim` only contains
 * valid numeric characters and optional sign symbols, then converts it
 * to an integer between 0 and 255. The result is stored in `val`.
 * 
 * @param trim Trimmed numeric string to convert.
 * @param val Pointer to an integer where the converted value will be stored.
 * @return 1 if the conversion succeeds and the value is valid, 0 otherwise.
 */
static int	check_and_convert_val(char *trim, int *val)
{
	long	v;

	if (*trim == '\0'
		|| ft_strspn(trim, "+-0123456789") != ft_strlen(trim))
		return (0);
	v = ft_atoi(trim);
	if (v < 0 || v > 255)
		return (0);
	*val = (int)v;
	return (1);
}

/**
 * @brief Extracts and validates RGB integer values from a string array.
 * 
 * This function expects an array of three strings (from a split on commas)
 * and attempts to parse each one into an integer RGB value using
 * `check_and_convert_val()`.
 * Each string is also trimmed of spaces before parsing.
 * 
 * @param sp Array of strings representing RGB values.
 * @param vals Output array where the three parsed integer values will be stored.
 * @return 1 if all three values are valid, 0 otherwise.
 */
static int	fill_vals_from_split(char **sp, int *vals)
{
	int		i;
	char	*trim;

	i = 0;
	while (i < 3)
	{
		if (!sp[i])
		{
			free_split(sp);
			return (0);
		}
		trim = strtrim_spaces(sp[i]);
		if (!check_and_convert_val(trim, &vals[i]))
		{
			free_split(sp);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief Parses a string representing an RGB triplet.
 * 
 * This function duplicates the input string, splits it by commas,
 * and converts the three resulting substrings into integer RGB components.
 * It validates that exactly three components are present and that each value
 * lies in the range [0, 255].
 * 
 * @param s Input string containing RGB values separated by commas.
 * @param out Pointer to the RGB structure to fill with parsed values.
 * @return 1 if parsing succeeds, 0 otherwise.
 */
static int	parse_rgb_triplet(const char *s, t_rgb *out)
{
	char	*mutable;
	char	**sp;
	int		vals[3];

	mutable = ft_strdup(s);
	if (!mutable)
		return (0);
	sp = ft_split(mutable, ',');
	free(mutable);
	if (!sp)
		return (0);
	if (!fill_vals_from_split(sp, vals))
		return (0);
	if (sp[3])
	{
		free_split(sp);
		return (0);
	}
	free_split(sp);
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
