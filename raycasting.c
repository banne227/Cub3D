/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:00:27 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/13 17:06:20 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	raycasting(t_game *game)
{
	int	x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int	mapX;
	int	mapY;
	double	deltaDistX;
	double	deltaDistY;
	int	stepX;
	int	stepY;
	double	sideDistX;
	double	sideDistY;
	int hit;
	double	perpWallDist;

	x = 0;
	while (x < game->win_w)
	{
		// 1. calcul direction rayon
		cameraX = 2 * x / (double)game->win_w - 1;
		rayDirX = game->player.dirX + game->player.planeX * cameraX;
		rayDirY = game->player.dirY + game->player.planeY * cameraX;
		// 2. dans quelle case de la map on est
		mapX = (int)game->player.posX;
		mapY = (int)game->player.posY;
		// 3. distance parcourue par le rayon pour aller d'une ligne x a la suivante
		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		// 4. DDA (Digital Differential Analysis) pour trouver le mur
		// Calculer stepX, stepY et sideDistX, sideDistY initial
		if (rayDirX < 0)
		{
			stepX = 1;
			sideDistX = (game->player.posX - mapX) *deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = 1;
			sideDistY = (game->player.posY - mapY) *deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1 - posY) * deltaDistY;
		}
		// Boucle jusqu'à toucher un mur
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX = stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += deltaDistY;
				side = 1;
			}
			if (game->map.map[mapX][mapY] > 0)
				hit = 1;
		}
		//Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perpWallDist = sideDistX - deltaDistX;
		else
			perpWallDist = sideDistY - deltaDistY;
		//Calculate height of line to draw on screen
		int line_height = (int)(game->win_h / perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
    	int drawStart = -line_height / 2 + game->win_h / 2;
    	int drawEnd = line_height / 2 + game->win_h / 2;
	}
}
