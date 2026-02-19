/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:10:54 by codespace         #+#    #+#             */
/*   Updated: 2026/02/19 10:36:47 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	cut(t_weapon *weapon, t_game *game)
{
	if (weapon->type == 1 || weapon->attack == 0)
		return ;
	if (weapon->frame == 0 || weapon->frame == 1)
		weapon->sound = play_sounds(KNIFE_SOUND);
	weapon->frame++;
	if (weapon->frame >= 100)
	{
		weapon->frame = 0;
		weapon->img = weapon->knife.img[0];
		weapon->height = weapon->knife.height1;
		weapon->width = weapon->knife.width1;
		weapon->attack = 0;
	}
	else
	{
		weapon->height = weapon->knife.height2;
		weapon->width = weapon->knife.width2;
		weapon->img = weapon->knife.img[1];
	}
	if (hit(weapon, game->player, game->map, game->ennemys))
		weapon->hit = 1;
}

int	hit(t_weapon *weapon, t_player player, t_map map, t_ennemy *ennemies)
{
	double	hit_x;
	double	hit_y;
	double	step_size;
	double	distance_traveled;

	hit_x = player.pos_x;
	hit_y = player.pos_y;
	step_size = 0.3;
	distance_traveled = 0.0;
	while (distance_traveled < weapon->knife.range)
	{
		hit_x += player.dir_x * step_size;
		hit_y += player.dir_y * step_size;
		distance_traveled += step_size;
		if ((int)hit_x < 0 || (int)hit_x >= map.width || (int)hit_y < 0
			|| (int)hit_y >= map.height)
			break ;
		if (map.map[(int)hit_y][(int)hit_x] == '1')
			return (0);
		if (map.map[(int)hit_y][(int)hit_x] == 'E')
		{
			take_damage(weapon->knife.damage, (int)hit_x, (int)hit_y, ennemies);
			return (1);
		}
	}
	return (0);
}
