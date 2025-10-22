/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:50:56 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 10:54:14 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include "cub3d.h"
#include "runtime.h"
#include "mlx.h"

int  render_frame(t_app *a);          // calcule et dessine une frame complète
void draw_vline(t_img *img, int x, int y0, int y1, int color);


#endif