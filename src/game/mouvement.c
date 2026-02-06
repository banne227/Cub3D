/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:07:09 by banne             #+#    #+#             */
/*   Updated: 2026/02/06 12:07:31 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void move_player(t_data *data, int keycode)
{
	double newPosX = -1;
	double newPosY = -1; 
	
	if (keycode == KEY_W)
	{
		newPosX = data->game.player.posX + data->game.player.dirX * MOVE_SPEED;
		newPosY = data->game.player.posY + data->game.player.dirY * MOVE_SPEED;
	}
	else if (keycode == KEY_S)
	{
		newPosX = data->game.player.posX - data->game.player.dirX * MOVE_SPEED;
		newPosY = data->game.player.posY - data->game.player.dirY * MOVE_SPEED;
	}
	else if (keycode == KEY_A)
	{
		newPosX = data->game.player.posX + data->game.player.dirY * MOVE_SPEED;
		newPosY = data->game.player.posY - data->game.player.dirX * MOVE_SPEED;
	}
	else if (keycode == KEY_D)
	{
		newPosX = data->game.player.posX - data->game.player.dirY * MOVE_SPEED;
		newPosY = data->game.player.posY + data->game.player.dirX * MOVE_SPEED;
	}
	if ( newPosX < 0 || newPosY < 0)
		return;
	if (!is_wall(&data->game.map, (int)newPosX, (int)data->game.player.posY))
	{
		data->game.player.posX = newPosX;
	}
	if (!is_wall(&data->game.map, (int)data->game.player.posX, (int)newPosY))
	{
		data->game.player.posY = newPosY;
	}
}

void rotate_player(t_data *data, int keycode)
{
	double oldDirX = data->game.player.dirX;
	double oldPlaneX = data->game.player.planeX;
	double rotSpeed = ROT_SPEED;

	if (keycode == KEY_LEFT)
		rotSpeed = -ROT_SPEED;
	else if (keycode != KEY_RIGHT)
		return;

	data->game.player.dirX = data->game.player.dirX * cos(rotSpeed) - data->game.player.dirY * sin(rotSpeed);
	data->game.player.dirY = oldDirX * sin(rotSpeed) + data->game.player.dirY * cos(rotSpeed);
	data->game.player.planeX = data->game.player.planeX * cos(rotSpeed) - data->game.player.planeY * sin(rotSpeed);
	data->game.player.planeY = oldPlaneX * sin(rotSpeed) + data->game.player.planeY * cos(rotSpeed);
}