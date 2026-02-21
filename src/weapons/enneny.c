/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enneny.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:21:06 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 18:05:43 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_ennemy *get_ennemy_at(int pos_x, int pos_y, t_ennemy *ennemies)
{
	while (ennemies)
	{
		if (ennemies->pos.x == pos_x && ennemies->pos.y == pos_y)
			return (ennemies);
		ennemies = ennemies->next;
	}
	return (NULL);
}

int take_damage(int damage, double pos_x, double pos_y, t_ennemy *ennemies)
{
	t_ennemy *ennemy;
	int x;
	int y;

	x = (int)pos_x;
	y = (int)pos_y;
	ennemy = get_ennemy_at(x, y, ennemies);
	if (!ennemy)
		return (0);
	if (ennemy->alive)
	{
		ennemy->hit_frame = 10;
		ennemy->health -= damage;
		if (ennemy->health <= 0)
		{
			ennemy->alive = false;
			ennemy->display = ennemy->img[3];
			play_sounds(DEATH_SOUND);
		}
		else
			play_sounds(BLOOD_SOUND);
	}
	return (1);
}
