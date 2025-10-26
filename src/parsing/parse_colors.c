/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:56:29 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 18:57:14 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
