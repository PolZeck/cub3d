/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:59:40 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/15 13:31:03 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// trim leading/trailing spaces of a string (in place)
static char	*strtrim_spaces(char *s)
{
	char *start = s;
	char *end;

	while (*start == ' ' || *start == '\t') start++;
	if (*start == '\0') return (start);
	end = start + ft_strlen(start) - 1;
	while (end > start && (*end == ' ' || *end == '\t')) end--;
	*(end + 1) = '\0';
	return (start);
}

static int parse_rgb_triplet(const char *s, t_rgb *out)
{
    // --- NEW: duplicate to drop const ---
    char    *mutable = ft_strdup(s);
    char    **sp;
    int     i, vals[3];

    if (!mutable)
        return 0;

    sp = ft_split(mutable, ',');   // your ft_split: char *str, char c
    free(mutable);                 // safe to free: ft_split copies each word
    if (!sp)
        return 0;

    for (i = 0; i < 3; ++i)
    {
        if (!sp[i]) { free_split(sp); return 0; }
        char *trim = /* same code as avant */ strtrim_spaces(sp[i]);
        if (*trim == '\0' || ft_strspn(trim, "+-0123456789") != ft_strlen(trim))
        { free_split(sp); return 0; }
        long v = ft_atoi(trim);
        if (v < 0 || v > 255) { free_split(sp); return 0; }
        vals[i] = (int)v;
    }
    if (sp[3]) { free_split(sp); return 0; }
    free_split(sp);

    out->r = vals[0]; out->g = vals[1]; out->b = vals[2];
    return 1;
}


int	parse_color_line(t_rgb *out, const char *rest)
{
	// rest pointe après 'F' ou 'C'
	char *p = (char *)rest;
	if (*p == '\0') return (0);
	// avancer d’au moins un espace
	p++;
	while (*p == ' ' || *p == '\t') p++;
	if (!*p) return (0);
	out->r = out->g = out->b = -1;
	return parse_rgb_triplet(p, out);
}
