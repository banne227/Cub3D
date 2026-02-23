/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:50:08 by codespace         #+#    #+#             */
/*   Updated: 2026/02/23 14:37:17 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	draw_crosshair(t_game *game)
{
	t_pos			pos;
	int				crosshair_index;
	t_dimensions	dim;

	dim.height = 16;
	dim.width = 16;
	pos.x = (game->win_w - 16) / 2;
	pos.y = (game->win_h - 16) / 2;
	crosshair_index = (game->weapon.hit != 0);
	if (game->weapon.crosshair[crosshair_index])
		draw_image_transparent(game, game->weapon.crosshair[crosshair_index],
			dim, pos);
	if (game->weapon.hit != 0)
	{
		game->weapon.hit++;
		if (game->weapon.hit > 15)
			game->weapon.hit = 0;
	}
}

void	draw_weapon(t_game *game)
{
	int	x;
	int	y;

	if (!game->weapon.img)
		return ;
	x = (game->win_w - 60) / 2;
	y = game->win_h - 128;
	draw_image_transparent(game, game->weapon.img,
		(t_dimensions){game->weapon.width, game->weapon.height}, (t_pos){x, y});
	draw_crosshair(game);
	display_ammo(&game->weapon, game);
}

int	swap_weapon(t_game *game)
{
	if (game->weapon.type == 0)
	{
		game->weapon.type = 1;
		game->weapon.img = game->weapon.gun.img;
		game->weapon.height = game->weapon.gun.dim.height;
		game->weapon.width = game->weapon.gun.dim.width;
	}
	else
	{
		game->weapon.type = 0;
		game->weapon.img = game->weapon.knife.img[0];
		game->weapon.height = game->weapon.knife.height1;
		game->weapon.width = game->weapon.knife.width1;
	}
	game->weapon.attack = 0;
	game->weapon.frame = 0;
	game->weapon.gun.fshoot = 0;
	game->weapon.gun.freload = 0;
	return (0);
}
