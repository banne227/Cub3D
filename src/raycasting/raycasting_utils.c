/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:11:21 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/19 17:26:58 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void dda(int ray_dir_x, int ray_dir_y, int side_dist_x, int side_dist_y, t_game *game, int map_x, int map_y, int delta_dist_x, int delta_dist_y)
{
	int step_x;
	int step_y;

	// 4. DDA (Digital Differential Analysis) pour trouver le mur
		// Calculer step_x, step_y et side_dist_x,	side_dist_y initial
	if (ray_dir_x < 0)
	{
		step_x = -1;
		side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (map_x + 1.0 - game->player.pos_x) * delta_dist_x;
	}
	if (ray_dir_y < 0)
	{
		step_y = -1;
		side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (map_y + 1.0 - game->player.pos_y) * delta_dist_y;
	}
}

void	touch_wall(int side_dist_x, int side_dist_y, int map_x, int map_y, int step_x, int step_y, int delta_dist_y, int delta_dist_x, t_game *game)
{
	int side;
	int	hit;

	// Boucle jusqu'à toucher un mur
	while (hit == 0)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
			side = 1;
		}
		if (game->map.map[map_y][map_x] == '1' || game->map.map[map_y][map_x] == 'D')
			hit = 1;
	}
}
