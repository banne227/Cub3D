/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 16:00:12 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:37:50 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	handle_mouse(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (data->game.state == STATE_PLAY)
		make_action(data, button);
	return (0);
}

int	handle_mouse_move(int x, int y, void *param)
{
	t_data			*data;
	t_mouse_mouv	mouse;

	data = (t_data *)param;
	mouse.center_x = WIN_W / 2;
	mouse.center_y = WIN_H / 2;
	if (data->game.state != STATE_PLAY ||
		(x == mouse.center_x && y == mouse.center_y))
		return (0);
	mouse.delta_x = x - mouse.center_x;
	mouse.rot_speed = mouse.delta_x * SENSI;
	mouse.olddir_x = data->game.player.dir_x;
	mouse.oldplane_x = data->game.player.plane_x;
	data->game.player.dir_x = data->game.player.dir_x * cos(mouse.rot_speed)
		- data->game.player.dir_y * sin(mouse.rot_speed);
	data->game.player.dir_y = mouse.olddir_x * sin(mouse.rot_speed)
		+ data->game.player.dir_y * cos(mouse.rot_speed);
	data->game.player.plane_x = data->game.player.plane_x * cos(mouse.rot_speed)
		- data->game.player.plane_y * sin(mouse.rot_speed);
	data->game.player.plane_y = mouse.oldplane_x * sin(mouse.rot_speed)
		+ data->game.player.plane_y * cos(mouse.rot_speed);
	mlx_mouse_move(data->game.mlx, data->game.win, mouse.center_x,
		mouse.center_y);
	return (0);
}
