/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 13:48:10 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 15:37:11 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	make_action2(t_data *data, int keycode)
{
	if (keycode == KEY_SPACE)
		swap_weapon(&data->game);
	else if (keycode == KEY_E)
	{
		open_door(&data->game.map,
			(int)(data->game.player.pos_x + data->game.player.dir_x),
			(int)(data->game.player.pos_y + data->game.player.dir_y));
	}
}

void	make_action(t_data *data, int keycode)
{
	t_player	player;

	player = data->game.player;
	if (keycode == MOUSE_LEFT)
	{
		if (data->game.weapon.type == 0)
			data->game.weapon.attack = 1;
		else if (data->game.weapon.type == 1 && data->game.weapon.gun.ammo > 0
			&& data->game.weapon.gun.freload == 0)
			data->game.weapon.attack = 1;
	}
	else if (keycode == MOUSE_RIGHT || keycode == 3 || keycode == KEY_R)
	{
		if (data->game.weapon.type == 1 && data->game.weapon.gun.ammo < 8
			&& data->game.weapon.gun.freload == 0)
			data->game.weapon.gun.freload = 1;
	}
	else if (keycode == KEY_M)
	{
		data->game.state = STATE_MENU;
		stop_background_music(&data->game);
	}
	else
		make_action2(data, keycode);
}
