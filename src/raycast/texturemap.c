/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texturemap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 10:09:42 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/23 10:22:20 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

/* quelle face toucher selon la normale du mur */
t_face	pick_face(int side, double rdx, double rdy)
{
	if (side == 0)              // mur vertical (E/W)
		return (rdx > 0 ? FACE_EA : FACE_WE);
	else                        // mur horizontal (N/S)
		return (rdy > 0 ? FACE_SO : FACE_NO);
}

// /* petite ombre côté Y pour relief */
// static int	tint_if_side(int color, int side)
// {
// 	if (!side)
// 		return (color);
// 	/* atténuation 50% environ */
// 	return ((color >> 1) & 0x7F7F7F);
// }
