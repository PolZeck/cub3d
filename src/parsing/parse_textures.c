/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:58:55 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/26 18:22:43 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
