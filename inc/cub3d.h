/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:21:59 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 10:36:58 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
}	t_textures;

typedef struct s_config
{
	t_textures	tx;
	t_rgb		floor;
	t_rgb		ceiling;

	char		**map;     // map normalisée (rectangulaire, paddée par ' ')
	int			map_w;
	int			map_h;

	int			player_x;  // case map (col)
	int			player_y;  // case map (row)
	char		player_dir; // 'N','S','E','W'
}	t_config;

/* ================= Parsing API ================= */
int		parse_config(const char *path, t_config *cfg);

/* ================ Parse helpers ================= */
int		parse_line_header(t_config *cfg, const char *line);
int		parse_texture_line(t_textures *tx, const char *id, const char *rest);
int		parse_color_line(t_rgb *out, const char *rest);
int		parse_map_collect(char ***lines_vec, int *size, int *cap, char *line);

/* ================ Normalize/Checks ============== */
int		normalize_map(t_config *cfg, char **raw_lines, int nlines);
int		validate_config(t_config *cfg);

/* ================== Utils / Errors ============== */
void	error_exit(const char *msg);
void	free_split(char **tab);
void	free_config(t_config *cfg);

/* ================== Internal checks ============= */
int		check_required_headers(const t_config *cfg);
int		check_map_chars_and_player(t_config *cfg);
int		check_map_closed(const t_config *cfg);

/* ================== Utils ============= */
int		ft_max(int a, int b);

#endif
