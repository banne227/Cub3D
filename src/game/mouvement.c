/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:07:09 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 12:49:14 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	move_player(t_game *game, int keycode)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = -1;
	newpos_y = -1;
	if (game->state != STATE_PLAY)
		return ;
	if (keycode == KEY_W)
	{
		newpos_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
		newpos_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		newpos_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
		newpos_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == KEY_A)
	{
		newpos_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED;
		newpos_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		newpos_x = game->player.pos_x - game->player.dir_y * MOVE_SPEED;
		newpos_y = game->player.pos_y + game->player.dir_x * MOVE_SPEED;
	}
	if (newpos_x < 0 || newpos_y < 0)
		return ;
	if (!is_wall(&game->map, (int)newpos_x, (int)game->player.pos_y))
	{
		game->player.pos_x = newpos_x;
	}
	if (!is_wall(&game->map, (int)game->player.pos_x, (int)newpos_y))
	{
		game->player.pos_y = newpos_y;
	}
}

void	rotate_player(t_data *data, int keycode)
{
	double	olddir_x;
	double	oldplane_x;
	double	rot_speed;

	olddir_x = data->game.player.dir_x;
	oldplane_x = data->game.player.plane_x;
	rot_speed = ROT_SPEED;
	if (keycode == KEY_LEFT)
		rot_speed = -ROT_SPEED;
	else if (keycode != KEY_RIGHT)
		return ;
	data->game.player.dir_x = data->game.player.dir_x * cos(rot_speed)
		- data->game.player.dir_y * sin(rot_speed);
	data->game.player.dir_y = olddir_x * sin(rot_speed)
		+ data->game.player.dir_y * cos(rot_speed);
	data->game.player.plane_x = data->game.player.plane_x * cos(rot_speed)
		- data->game.player.plane_y * sin(rot_speed);
	data->game.player.plane_y = oldplane_x * sin(rot_speed)
		+ data->game.player.plane_y * cos(rot_speed);
}
