/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:06:57 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/27 10:32:03 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "runtime.h"
#include "mlx.h"

/**
 * @brief Load a texture from an XPM file using MiniLibX.
 *
 * Loads an XPM image file and retrieves its address, dimensions,
 * and format information. Returns 0 if loading or data retrieval
 * fails.
 *
 * @param a    Pointer to the application context (contains MLX ptr).
 * @param path Path to the XPM texture file.
 * @param out  Pointer to the texture structure to fill.
 * @return 1 on success, 0 on failure.
 */
static int	load_xpm(t_app *a, const char *path, t_img *out)
{
	out->img = mlx_xpm_file_to_image(a->mlx, (char *)path, &out->w, &out->h);
	if (!out->img)
		return (0);
	out->addr = mlx_get_data_addr(out->img, &out->bpp,
			&out->line_len, &out->endian);
	if (!out->addr)
		return (0);
	return (1);
}

/**
 * @brief Load all wall textures defined in the configuration.
 *
 * Loads the four cardinal wall textures (NO, SO, WE, EA) using MLX.
 * If any texture fails to load, the program exits cleanly with an
 * error message.
 *
 * @param a Pointer to the application context.
 * @return 1 on success (all textures loaded correctly).
 */
int	load_textures(t_app *a)
{
	if (!load_xpm(a, a->cfg.tx.no, &a->tex.no))
		error_exit_app("Error\nNO texture load", a);
	if (!load_xpm(a, a->cfg.tx.so, &a->tex.so))
		error_exit_app("Error\nSO texture load", a);
	if (!load_xpm(a, a->cfg.tx.we, &a->tex.we))
		error_exit_app("Error\nWE texture load", a);
	if (!load_xpm(a, a->cfg.tx.ea, &a->tex.ea))
		error_exit_app("Error\nEA texture load", a);
	return (1);
}

/**
 * @brief Destroy all loaded wall textures and free MLX resources.
 *
 * Destroys each texture image previously loaded by MLX, if it exists.
 * This function is safe to call even if some textures failed to load.
 *
 * @param a Pointer to the application context.
 */
void	destroy_textures(t_app *a)
{
	if (a->tex.no.img)
		mlx_destroy_image(a->mlx, a->tex.no.img);
	if (a->tex.so.img)
		mlx_destroy_image(a->mlx, a->tex.so.img);
	if (a->tex.we.img)
		mlx_destroy_image(a->mlx, a->tex.we.img);
	if (a->tex.ea.img)
		mlx_destroy_image(a->mlx, a->tex.ea.img);
}

/**
 * @brief Retrieve a single pixel color from a texture.
 *
 * Clamps the texture coordinates (u, v) to the valid range
 * and returns the 24-bit color value located at that position
 * in the texture buffer.
 *
 * @param tex Pointer to the texture image.
 * @param u   Horizontal texture coordinate (X).
 * @param v   Vertical texture coordinate (Y).
 * @return 24-bit RGB color (0xRRGGBB) of the texel.
 */
int	texel_at(const t_img *tex, int u, int v)
{
	char	*p;

	if (u < 0)
		u = 0;
	if (v < 0)
		v = 0;
	if (u >= tex->w)
		u = tex->w - 1;
	if (v >= tex->h)
		v = tex->h - 1;
	p = tex->addr + v * tex->line_len + u * (tex->bpp / 8);
	return (*(int *)p);
}
