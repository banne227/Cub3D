/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 17:15:59 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 17:17:51 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	update_player_data2(t_data *data, char d)
{
	if (d == 'E')
	{
		data->game.player.dir_x = 1;
		data->game.player.dir_y = 0;
		data->game.player.plane_x = 0;
		data->game.player.plane_y = 0.66;
	}
	else if (d == 'W')
	{
		data->game.player.dir_x = -1;
		data->game.player.dir_y = 0;
		data->game.player.plane_x = 0;
		data->game.player.plane_y = -0.66;
	}
}

void	update_player_data(t_data *data, char d)
{
	if (d == 'N')
	{
		data->game.player.dir_x = 0;
		data->game.player.dir_y = -1;
		data->game.player.plane_x = 0.66;
		data->game.player.plane_y = 0;
	}
	else if (d == 'S')
	{
		data->game.player.dir_x = 0;
		data->game.player.dir_y = 1;
		data->game.player.plane_x = -0.66;
		data->game.player.plane_y = 0;
	}
	else
		update_player_data2(data, d);
}
