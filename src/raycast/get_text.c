/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:39:36 by pledieu           #+#    #+#             */
/*   Updated: 2025/11/06 15:20:09 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "runtime.h"
#include "raycast.h"

static t_face	pick_face(int side, double rdx, double rdy)
{
	if (side == 0)
	{
		if (rdx > 0)
			return (FACE_EA);
		return (FACE_WE);
	}
	if (rdy > 0)
		return (FACE_SO);
	return (FACE_NO);
}

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
