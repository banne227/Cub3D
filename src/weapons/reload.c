/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:10:58 by codespace         #+#    #+#             */
/*   Updated: 2026/02/19 11:15:21 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	reload(t_weapon *weapon)
{
	if (weapon->type == 0 || weapon->gun.ammo == 8)
		return ;
	if (weapon->gun.freload == 0 || weapon->gun.freload == 1)
	{
		weapon->sound = play_sounds(RELOAD_SOUND);
	}
	weapon->gun.freload++;
	if (weapon->gun.freload % 80 == 0 && weapon->gun.freload / 80 < 4)
	{
		weapon->img = weapon->gun.reload[weapon->gun.freload / 80];
		weapon->height = weapon->gun.dim_reload[weapon->gun.freload
			/ 80].height;
		weapon->width = weapon->gun.dim_reload[weapon->gun.freload / 80].width;
	}
	if (weapon->gun.freload >= 320)
	{
		weapon->img = weapon->gun.img;
		weapon->gun.freload = 0;
		weapon->gun.ammo = 8;
		weapon->height = weapon->gun.dim.height;
		weapon->width = weapon->gun.dim.width;
	}
}