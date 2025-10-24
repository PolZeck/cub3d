/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:06:57 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/23 10:07:50 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "runtime.h"
#include "mlx.h"

/* charge un xpm dans un t_img */
static int	load_xpm(t_app *a, const char *path, t_img *out)
{
	out->img = mlx_xpm_file_to_image(a->mlx, (char *)path, &out->w, &out->h);
	if (!out->img)
		return (0);
	out->addr = mlx_get_data_addr(out->img, &out->bpp, &out->line_len, &out->endian);
	if (!out->addr)
		return (0);
	return (1);
}

int	load_textures(t_app *a)
{
	if (!load_xpm(a, a->cfg.tx.no, &a->tex.no)) error_exit("Error\nNO texture load");
	if (!load_xpm(a, a->cfg.tx.so, &a->tex.so)) error_exit("Error\nSO texture load");
	if (!load_xpm(a, a->cfg.tx.we, &a->tex.we)) error_exit("Error\nWE texture load");
	if (!load_xpm(a, a->cfg.tx.ea, &a->tex.ea)) error_exit("Error\nEA texture load");
	return (1);
}

void	destroy_textures(t_app *a)
{
	if (a->tex.no.img) mlx_destroy_image(a->mlx, a->tex.no.img);
	if (a->tex.so.img) mlx_destroy_image(a->mlx, a->tex.so.img);
	if (a->tex.we.img) mlx_destroy_image(a->mlx, a->tex.we.img);
	if (a->tex.ea.img) mlx_destroy_image(a->mlx, a->tex.ea.img);
}

/* lecture d’un pixel (32bpp attendu) */
int	texel_at(const t_img *tex, int u, int v)
{
	char	*p;

	if (u < 0) u = 0;
	if (v < 0) v = 0;
	if (u >= tex->w) u = tex->w - 1;
	if (v >= tex->h) v = tex->h - 1;
	p = tex->addr + v * tex->line_len + u * (tex->bpp / 8);
	return (*(int *)p);
}
