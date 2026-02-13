/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:00:27 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/13 18:07:52 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	raycasting(t_game *game)
{
	int		x;
	double	camera_x;
	double	rayDir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit;
	double	perp_wall_dist;
	int		side;
	int		line_height;
	int		drawStart;
	int		drawEnd;

	x = 0;
	while (x < game->win_w)
	{
		// 1. calcul direction rayon
		camera_x = 2 * x / (double)game->win_w - 1;
		rayDir_x = game->player.dir_x + game->player.plane_x * camera_x;
		ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
		// 2. dans quelle case de la map on est
		map_x = (int)game->player.pos_x;
		map_y = (int)game->player.pos_y;
		// 3. distance parcourue par le rayon pour aller d'une ligne x a la suivante
		delta_dist_x = fabs(1 / rayDir_x);
		delta_dist_y = fabs(1 / ray_dir_y);
		// 4. DDA (Digital Differential Analysis) pour trouver le mur
		// Calculer step_x, step_y et side_dist_x,	side_dist_y initial
		if (rayDir_x < 0)
		{
			step_x = 1;
			side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1 - game->player.pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = 1;
			side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1 - game->player.pos_y) * delta_dist_y;
		}
		// Boucle jusqu'à toucher un mur
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x = step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += delta_dist_y;
				side = 1;
			}
			if (game->map.map[map_x][map_y] > 0)
				hit = 1;
		}
		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		// Calculate height of line to draw on screen
		line_height = (int)(game->win_h / perp_wall_dist);
		// calculate lowest and highest pixel to fill in current stripe
		drawStart = -line_height / 2 + game->win_h / 2;
		drawEnd = line_height / 2 + game->win_h / 2;
	}
}
