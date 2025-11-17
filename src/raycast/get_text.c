/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcosson <lcosson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:39:36 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/17 11:34:16 by lcosson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

/**
 * @brief Determines which wall face (N/S/E/W) was hit by the ray.
 *
 * This function decides which texture face to use based on the
 * side of the wall intersection and the sign of the ray direction.
 *
 * @param side The side of the wall hit (0 for vertical, 1 for horizontal).
 * @param rdx  The x-component of the ray direction.
 * @param rdy  The y-component of the ray direction.
 * @return The corresponding face enumeration (FACE_NO, FACE_SO,
 *         FACE_WE, FACE_EA).
 */
static t_face	pick_face(int side, double rdx, double rdy)
{
	if (side == 0)
	{
		if (rdx > 0)
			return (FACE_WE);
		return (FACE_EA);
	}
	else
	{
		if (rdy > 0)
			return (FACE_NO);
		return (FACE_SO);
	}
}

/**
 * @brief Retrieves the correct texture image based on the ray impact.
 *
 * This function uses the ray direction and the hit side to determine
 * which wall face (North, South, West, East) was struck, and returns
 * the corresponding texture from the texture set.
 *
 * @param a Pointer to the main application structure.
 * @param r Pointer to the current ray containing hit information.
 * @return A pointer to the texture image corresponding to the hit wall.
 */
const t_img	*get_tex(t_app *a, const t_ray *r)
{
	t_face	f;

	f = pick_face(r->side, r->ray_dir.x, r->ray_dir.y);
	if (f == FACE_NO)
		return (&a->tex.no);
	if (f == FACE_SO)
		return (&a->tex.so);
	if (f == FACE_WE)
		return (&a->tex.we);
	return (&a->tex.ea);
}
