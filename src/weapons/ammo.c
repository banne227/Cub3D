/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:06:37 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 09:32:23 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void display_ammo(t_weapon *weapon, t_game *game)
{
	int x;
	int y;
	int count;

	if (weapon->type == 0)
		return;
	x = 5;
	y = 675;
	count = 0;
	while (count < MAX_AMMO)
	{
		if (count < weapon->gun.ammo)
			draw_image_transparent(game, weapon->ammo[0], 18, 38, x, y);
		else
			draw_image_transparent(game, weapon->ammo[1], 18, 38, x, y);
		x += 18;
		count++;
	}
}
