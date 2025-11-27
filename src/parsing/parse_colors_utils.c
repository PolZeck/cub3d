/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:56:29 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/27 15:55:13 by lcosson          ###   ########.fr       */
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

int	check_coma(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		if (count > 2)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Extracts 3 integer RGB values from a mutable comma-separated string.
 *
 * This function assumes the string is already verified to contain exactly
 * two commas. It splits the string, checks that exactly 3 fields are present,
 * converts them into ints inside `vals`, and frees the split array.
 *
 * @param s Mutable string to split (will NOT be freed).
 * @param vals Output array of 3 integers.
 * @return 1 on success, 0 on failure.
 */
int	extract_rgb_values(char *s, int vals[3])
{
	char	**sp;

	sp = ft_split(s, ',');
	if (!sp)
		return (0);
	if (!fill_vals_from_split(sp, vals) || sp[3])
		return (0);
	free_split(sp);
	return (1);
}
