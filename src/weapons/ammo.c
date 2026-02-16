/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:06:37 by banne             #+#    #+#             */
/*   Updated: 2026/02/16 11:14:52 by banne            ###   ########.fr       */
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
			mlx_put_image_to_window(game->mlx, game->win, weapon->ammo[0], x, y);
		else
			mlx_put_image_to_window(game->mlx, game->win, weapon->ammo[1], x, y);
		x += 18;
		count++;
	}
}
	