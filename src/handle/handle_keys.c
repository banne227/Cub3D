/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 15:59:59 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 18:20:05 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	case_keycode_m(t_data *data, int keycode)
{
	if (keycode == KEY_M)
	{
		if (data->game.state == STATE_MENU)
		{
			data->game.state = STATE_PLAY;
		}
		else if (data->game.state == STATE_PLAY)
		{
			data->game.state = STATE_MENU;
			stop_background_music(&data->game);
		}
		return (1);
	}
	return (0);
}

int	handle_key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->game.keys[keycode] = true;
	data->game.last_key = keycode;
	if (keycode == KEY_ESC || data->game.state == STATE_EXIT)
		return (close_game(data));
	if	(case_keycode_m(data, keycode))
		return (0);
	if (data->game.state == STATE_PLAY)
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
	return (0);
}

int handle_keys_release(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->game.keys[keycode] = false;
	return (0);
}
