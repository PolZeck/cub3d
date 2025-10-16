/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:58:55 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/15 12:59:22 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*dup_trim_path(const char *s)
{
	// consommer l’identifiant déjà géré en amont, ici s pointe sur " <path>"
	char *p = (char *)s;
	p = (char *) (p + 1); // sauter au moins un espace après l’ID
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p == '\0')
		return (NULL);
	// trim finaux
	size_t len = ft_strlen(p);
	while (len && (p[len-1] == ' ' || p[len-1] == '\t')) len--;
	return (ft_substr(p, 0, len));
}

int	parse_texture_line(t_textures *tx, const char *id, const char *rest)
{
	char *path = dup_trim_path(rest);
	if (!path)
		return (0);

	if (!ft_strncmp(id, "NO", 2)) {
		if (tx->no) { free(path); return (0); }
		tx->no = path;
	}
	else if (!ft_strncmp(id, "SO", 2)) {
		if (tx->so) { free(path); return (0); }
		tx->so = path;
	}
	else if (!ft_strncmp(id, "WE", 2)) {
		if (tx->we) { free(path); return (0); }
		tx->we = path;
	}
	else if (!ft_strncmp(id, "EA", 2)) {
		if (tx->ea) { free(path); return (0); }
		tx->ea = path;
	}
	else {
		free(path);
		return (0);
	}
	return (1);
}

int	check_required_headers(const t_config *cfg)
{
	if (!cfg->tx.no || !cfg->tx.so || !cfg->tx.we || !cfg->tx.ea)
		return (0);
	// 0 <= rgb <= 255 et init: on considère init OK si la somme >= 0
	if (cfg->floor.r < 0 || cfg->floor.g < 0 || cfg->floor.b < 0) return (0);
	if (cfg->ceiling.r < 0 || cfg->ceiling.g < 0 || cfg->ceiling.b < 0) return (0);
	return (1);
}
