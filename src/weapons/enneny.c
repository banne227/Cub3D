/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enneny.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 08:21:06 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 08:21:06 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_ennemy	*get_ennemy_at(int pos_x, int pos_y, t_ennemy *ennemies)
{
	while (ennemies)
	{
		if (ennemies->pos.x == pos_x && ennemies->pos.y == pos_y)
			return (ennemies);
		ennemies = ennemies->next;
	}
	return (NULL);
}

void	take_damage(int damage, int pos_x, int pos_y, t_ennemy *ennemies)
{
	t_ennemy *ennemy;

	ennemy = get_ennemy_at(pos_x, pos_y, ennemies);
	if (!ennemy)
		return ;
	ennemy->display = ennemy->img[2];
	if (ennemy->alive)
	{
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
}