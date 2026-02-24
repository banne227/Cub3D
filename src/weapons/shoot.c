/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:11:01 by codespace         #+#    #+#             */
/*   Updated: 2026/02/24 11:25:49 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	shoot(t_weapon *weapon, t_game *game)
{
	if (weapon->type == 0 || weapon->attack == 0 || weapon->gun.ammo == 0
		|| weapon->gun.freload > 0)
		return ;
	if (weapon->gun.fshoot == 0)
	{
		play_sounds(SHOOT_SOUND);
		if (bullet_hit(weapon, game->player, game->map, game->ennemys))
			weapon->hit = 1;
		weapon->gun.ammo--;
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
		weapon->height = weapon->gun.dim.height;
		weapon->width = weapon->gun.dim.width;
	}
}

bool	is_ennemy(double pos_x, double pos_y, t_ennemy *ennemies)
{
	double	dist_x;
	double	dist_y;
	double	radius;

	radius = 0.15;
	while (ennemies)
	{
		dist_x = pos_x - (ennemies->pos.x + 0.5);
		dist_y = pos_y - (ennemies->pos.y + 0.5);
		if (dist_x * dist_x + dist_y * dist_y < radius * radius)
			return (true);
		ennemies = ennemies->next;
	}
	return (false);
}

int	bullet_hit(t_weapon *weapon, t_player player, t_map map, t_ennemy *ennemies)
{
	double	bullet_x;
	double	bullet_y;
	double	step_size;
	double	distance_traveled;

	bullet_x = player.pos_x;
	bullet_y = player.pos_y;
	step_size = 0.1;
	distance_traveled = 0.0;
	while (distance_traveled < weapon->gun.range)
	{
		bullet_x += player.dir_x * step_size;
		bullet_y += player.dir_y * step_size;
		distance_traveled += step_size;
		if ((int)bullet_x < 0 || (int)bullet_x >= map.width
			|| (int)bullet_y >= map.height || (int)bullet_y < 0
			|| map.map[(int)bullet_y][(int)bullet_x] == '1')
			break ;
		if (is_ennemy(bullet_x, bullet_y, ennemies)
			&& is_alive((int)bullet_x, (int)bullet_y, ennemies))
			return (take_damage(weapon->gun.damage, bullet_x, bullet_y,
					ennemies));
	}
	return (0);
}
