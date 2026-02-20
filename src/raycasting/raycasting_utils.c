/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:11:21 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/20 14:38:55 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	dda(t_raycasting_utils *utils, t_game *game)
{
	// 4. DDA (Digital Differential Analysis) pour trouver le mur
		// Calculer step_x, step_y et side_dist_x,	side_dist_y initial
	if (utils->ray_dir_x < 0)
	{
		utils->step_x = -1;
		utils->side_dist_x = (game->player.pos_x - utils->map_x)
			* utils->delta_dist_x;
	}
	else
	{
		utils->step_x = 1;
		utils->side_dist_x = (utils->map_x + 1.0 - game->player.pos_x)
			* utils->delta_dist_x;
	}
	if (utils->ray_dir_y < 0)
	{
		utils->step_y = -1;
		utils->side_dist_y = (game->player.pos_y - utils->map_y)
			* utils->delta_dist_y;
	}
	else
	{
		utils->step_y = 1;
		utils->side_dist_y = (utils->map_y + 1.0 - game->player.pos_y)
			* utils->delta_dist_y;
	}
}

void	touch_wall(t_raycasting_utils *utils, t_game *game)
{
	// Boucle jusqu'à toucher un mur
	while (utils->hit == 0)
	{
		if (utils->side_dist_x < utils->side_dist_y)
		{
			utils->side_dist_x += utils->delta_dist_x;
			utils->map_x += utils->step_x;
			utils->side = 0;
		}
		else
		{
			utils->side_dist_y += utils->delta_dist_y;
			utils->map_y += utils->step_y;
			utils->side = 1;
		}
		if (game->map.map[utils->map_y][utils->map_x] == '1'
				|| game->map.map[utils->map_y][utils->map_x] == 'D')
			utils->hit = 1;
	}
}

int	convert_coords_textures(t_raycasting_utils *utils, t_game *game)
{
	int		img_x;
	double	wall_x;

	if (utils->side == 0)
		wall_x = game->player.pos_y + utils->perp_wall_dist * utils->ray_dir_y;
	else
		wall_x = game->player.pos_x + utils->perp_wall_dist * utils->ray_dir_x;
	wall_x -= floor(wall_x); // garder partie decimale
	// convert en coords x de texture
	img_x = (int)(wall_x * (double)utils->img->width);
	if (img_x >= utils->img->width)
		img_x = utils->img->width - 1;
	if (img_x < 0)
		img_x = 0;
	if (utils->side == 0 && utils->ray_dir_x < 0)
		img_x = utils->img->width - img_x - 1;
	if (utils->side == 1 && utils->ray_dir_y > 0)
		img_x = utils->img->width - img_x - 1;
	return (img_x);
}

int	pixel_to_fill(t_raycasting_utils *utils, t_game *game)
{
	int	line_height;

	// Calculate height of line to draw on screen
	line_height = (int)(game->win_h / utils->perp_wall_dist);
	// calculate lowest and highest pixel to fill in current stripe
	utils->draw_start = -line_height / 2 + game->win_h / 2;
	utils->draw_end = line_height / 2 + game->win_h / 2;
	if (utils->draw_start < 0)
		utils->draw_start = 0;
	if (utils->draw_end >= game->win_h)
		utils->draw_end = game->win_h - 1;
	return (line_height);
}

void	calculate_ray_dir(t_raycasting_utils *utils, t_game *game, int x)
{
	utils->hit = 0;
	// 1. calcul direction rayon
	utils->camera_x = 2 * x / (double)game->win_w - 1;
	utils->ray_dir_x = game->player.dir_x + game->player.plane_x
		* utils->camera_x;
	utils->ray_dir_y = game->player.dir_y + game->player.plane_y
		* utils->camera_x;
}
