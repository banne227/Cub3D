/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ammo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 09:06:37 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 14:54:57 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	display_ammo(t_weapon *weapon, t_game *game)
{
	t_pos			pos;
	int				count;
	t_dimensions	dim;

	if (weapon->type == 0)
		return ;
	pos.x = 5;
	pos.y = 675;
	count = 0;
	dim.height = 38;
	dim.width = 18;
	while (count < MAX_AMMO)
	{
		if (count < weapon->gun.ammo)
			draw_image_transparent(game, weapon->ammo[0], dim, pos);
		else
			draw_image_transparent(game, weapon->ammo[1], dim, pos);
		pos.x += 18;
		count++;
	}
}
