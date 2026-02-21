/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:11:01 by codespace         #+#    #+#             */
/*   Updated: 2026/02/19 11:15:31 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void shoot(t_weapon *weapon, t_game *game)
{
	pid_t sound;

	sound = 0;
	if (weapon->type == 0 || weapon->attack == 0 || weapon->gun.ammo == 0 || weapon->gun.freload > 0)
		return;
	if (weapon->gun.fshoot == 0)
	{
		sound = play_sounds(SHOOT_SOUND);
		if (sound && sound > 0)
			weapon->sound = sound;
		if (bullet_hit(weapon, game->player, game->map, game->ennemys))
			weapon->hit = 1;
	}
	weapon->gun.fshoot++;
	if (weapon->gun.fshoot % 15 == 0 && weapon->gun.fshoot / 15 < 6)
	{
		weapon->img = weapon->gun.shoot[weapon->gun.fshoot / 15];
		weapon->height = weapon->gun.dim_shoot[weapon->gun.fshoot / 15].height;
		weapon->width = weapon->gun.dim_shoot[weapon->gun.fshoot / 15].width;
	}
	if (weapon->gun.fshoot >= 90)
	{
		weapon->img = weapon->gun.img;
		weapon->attack = 0;
		weapon->gun.fshoot = 0;
		weapon->gun.ammo--;
		weapon->height = weapon->gun.dim.height;
		weapon->width = weapon->gun.dim.width;
	}
}

int bullet_hit(t_weapon *weapon, t_player player, t_map map, t_ennemy *ennemies)
{
	double bullet_x;
	double bullet_y;
	double step_size;
	double distance_traveled;

	bullet_x = player.pos_x;
	bullet_y = player.pos_y;
	step_size = 0.1;
	distance_traveled = 0.0;
	while (distance_traveled < weapon->gun.range)
	{
		bullet_x += player.dir_x * step_size;
		bullet_y += player.dir_y * step_size;
		distance_traveled += step_size;
		if ((int)bullet_x < 0 || (int)bullet_x >= map.width || (int)bullet_y < 0 || (int)bullet_y >= map.height)
			break;
		if (map.map[(int)bullet_y][(int)bullet_x] == '1')
			return (0);
		if (map.map[(int)bullet_y][(int)bullet_x] == 'M')
		{
			take_damage(weapon->gun.damage, bullet_x, bullet_y,
						ennemies);
			return (1);
		}
	}
	return (0);
}
