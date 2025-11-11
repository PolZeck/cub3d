/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:58:55 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/11 13:42:12 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Duplicates a texture path string while trimming surrounding whitespace.
 * 
 * This function skips the identifier prefix (e.g. "NO", "SO", "WE", "EA"),
 * then trims leading and trailing spaces or tabs from the remaining path.
 * The cleaned substring is duplicated using `ft_substr()` and returned.
 * 
 * @param s Input string containing the texture path (after the identifier).
 * @return Newly allocated trimmed string, 
 * or NULL if the path is empty or invalid.
 */
static char	*dup_trim_path(const char *s)
{
	size_t	len;
	char	*p;

	p = (char *)s;
	p = (char *)(p + 1);
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == '\0')
		return (NULL);
	len = ft_strlen(p);
	while (len && (p[len -1] == ' ' || p[len -1] == '\t'))
		len--;
	return (ft_substr(p, 0, len));
}

/**
 * @brief Assigns a texture path to a target field if it is not already set.
 * 
 * This function assigns the provided `path` to the destination pointer `dst`.
 * If the destination is already assigned, it frees the new path and returns 0
 * to indicate a duplicate header error.
 * 
 * @param dst Pointer to the destination string in the texture structure.
 * @param path Newly allocated texture path string.
 * @return 1 if assignment succeeds, 0 if the destination was already set.
 */
static int	assign_texture_path(char **dst, char *path)
{
	if (*dst)
	{
		free(path);
		return (0);
	}
	*dst = path;
	return (1);
}

/**
 * @brief Parses a texture definition line and assigns the corresponding path.
 * 
 * This function processes a configuration line for one of the texture headers:
 * - "NO" (north)
 * - "SO" (south)
 * - "WE" (west)
 * - "EA" (east)
 * 
 * The path string is trimmed of spaces and stored in the corresponding field
 * of the `t_textures` structure.
 * 
 * @param tx Pointer to the textures structure.
 * @param id Two-letter texture identifier ("NO", "SO", "WE", or "EA").
 * @param rest Remaining part of the line after the identifier.
 * @return 1 if parsing and assignment succeed, 0 otherwise.
 */
int	parse_texture_line(t_textures *tx, const char *id, const char *rest)
{
	char	*path;

	path = dup_trim_path(rest);
	if (!path)
		return (0);
	if (!ft_strncmp(id, "NO", 2))
		return (assign_texture_path(&tx->no, path));
	else if (!ft_strncmp(id, "SO", 2))
		return (assign_texture_path(&tx->so, path));
	else if (!ft_strncmp(id, "WE", 2))
		return (assign_texture_path(&tx->we, path));
	else if (!ft_strncmp(id, "EA", 2))
		return (assign_texture_path(&tx->ea, path));
	free(path);
	return (0);
}

/**
 * @brief Checks if all required texture and color headers are present.
 * 
 * This function verifies that all four texture paths ("NO", "SO", "WE", "EA")
 * have been successfully assigned and that both the floor and ceiling colors
 * have valid RGB values (non-negative).
 * 
 * @param cfg Pointer to the configuration structure to validate.
 * @return 1 if all required headers are present and valid, 0 otherwise.
 */
int	check_required_headers(const t_config *cfg)
{
	if (!cfg->tx.no || !cfg->tx.so || !cfg->tx.we || !cfg->tx.ea)
		return (0);
	if (cfg->floor.r < 0 || cfg->floor.g < 0 || cfg->floor.b < 0)
		return (0);
	if (cfg->ceiling.r < 0 || cfg->ceiling.g < 0 || cfg->ceiling.b < 0)
		return (0);
	return (1);
}
