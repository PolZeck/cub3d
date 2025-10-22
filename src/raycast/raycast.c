/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pledieu <pledieu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 10:52:15 by pledieu           #+#    #+#             */
/*   Updated: 2025/10/22 10:52:24 by pledieu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include <math.h>

// petite ligne verticale
void draw_vline(t_img *img, int x, int y0, int y1, int color)
{
    if (x < 0 || x >= img->w) return;
    if (y0 < 0) y0 = 0;
    if (y1 >= img->h) y1 = img->h - 1;
    for (int y = y0; y <= y1; ++y)
        put_px(img, x, y, color);
}

// couleurs simples pour déboguer : N/S/E/W et ombrage côté
static int side_tint(int base, int side) {
    if (!side) return base;           // mur X
    // atténuer un peu pour les murs Y
    int r = ((base >> 16) & 0xFF) * 0.8;
    int g = ((base >> 8)  & 0xFF) * 0.8;
    int b = ( base        & 0xFF) * 0.8;
    return ( ((r&0xFF)<<16) | ((g&0xFF)<<8) | (b&0xFF) );
}

int render_frame(t_app *a)
{
    // fond plafond/sol
    fill_half_screens(a);

    // paramètres
    const double posX = a->pl.pos_x;
    const double posY = a->pl.pos_y;
    const double dirX = a->pl.dir_x;
    const double dirY = a->pl.dir_y;
    const double planeX = a->pl.plane_x;
    const double planeY = a->pl.plane_y;

    for (int x = 0; x < a->frame.w; ++x)
    {
        // rayon pour cette colonne
        double cameraX = 2.0 * x / (double)a->frame.w - 1.0; // [-1,1]
        double rayDirX = dirX + planeX * cameraX;
        double rayDirY = dirY + planeY * cameraX;

        // case de départ dans la map
        int mapX = (int)posX;
        int mapY = (int)posY;

        // longueur de rayon pour passer d’une ligne de grille à la suivante
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1.0 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1.0 / rayDirY);
        double sideDistX, sideDistY;
        int stepX, stepY;

        // init du DDA
        if (rayDirX < 0) { stepX = -1; sideDistX = (posX - mapX) * deltaDistX; }
        else             { stepX =  1; sideDistX = (mapX + 1.0 - posX) * deltaDistX; }
        if (rayDirY < 0) { stepY = -1; sideDistY = (posY - mapY) * deltaDistY; }
        else             { stepY =  1; sideDistY = (mapY + 1.0 - posY) * deltaDistY; }

        // DDA jusqu’au mur
        int hit = 0, side = 0;
        while (!hit)
        {
            if (sideDistX < sideDistY) { sideDistX += deltaDistX; mapX += stepX; side = 0; }
            else                        { sideDistY += deltaDistY; mapY += stepY; side = 1; }

            // sortir si hors limites (sécurité)
            if (mapX < 0 || mapY < 0 || mapX >= a->cfg.map_w || mapY >= a->cfg.map_h) { hit = 1; break; }
            if (a->cfg.map[mapY][mapX] == '1') hit = 1;
        }

        // distance perpendiculaire au mur
        double perpWallDist;
        if (side == 0) perpWallDist = (mapX - posX + (1 - stepX) / 2.0) / (rayDirX == 0 ? 1e-6 : rayDirX);
        else           perpWallDist = (mapY - posY + (1 - stepY) / 2.0) / (rayDirY == 0 ? 1e-6 : rayDirY);
        if (perpWallDist < 1e-6) perpWallDist = 1e-6;

        // hauteur de la colonne
        int lineHeight = (int)(a->frame.h / perpWallDist);
        int drawStart = -lineHeight / 2 + a->frame.h / 2;
        int drawEnd   =  lineHeight / 2 + a->frame.h / 2;

        // couleur “debug” selon la face frappée
        int base = 0x55AAFF; // par défaut
        if (side == 0) base = (rayDirX > 0) ? 0xFF4444 : 0x44FF44; // E : rouge / W : vert
        else           base = (rayDirY > 0) ? 0x4444FF : 0xFFFF44; // S : bleu / N : jaune

        int color = side_tint(base, side);
        draw_vline(&a->frame, x, drawStart, drawEnd, color);
    }

    return 0;
}
