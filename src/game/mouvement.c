/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvement.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 12:07:09 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:27:49 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	other_move(t_game *game, double *pos_x, double *pos_y)
{
	if (game->keys[KEY_S])
	{
		*pos_x = game->player.pos_x - game->player.dir_x * MOVE_SPEED;
		*pos_y = game->player.pos_y - game->player.dir_y * MOVE_SPEED;
	}
	if (game->keys[KEY_A])
	{
		*pos_x = game->player.pos_x - game->player.plane_x * MOVE_SPEED / 2;
		*pos_y = game->player.pos_y - game->player.plane_y * MOVE_SPEED / 2;
	}
	if (game->keys[KEY_D])
	{
		*pos_x = game->player.pos_x + game->player.plane_x * MOVE_SPEED / 2;
		*pos_y = game->player.pos_y + game->player.plane_y * MOVE_SPEED / 2;
	}
}

void	move_player(t_game *game)
{
	double	newpos_x;
	double	newpos_y;

	newpos_x = -1;
	newpos_y = -1;
	if (game->state != STATE_PLAY)
		return ;
	if (game->keys[KEY_W])
	{
		newpos_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED;
		newpos_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED;
	}
	other_move(game, &newpos_x, &newpos_y);
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

void	rotate_player(t_data *data)
{
	double	olddir_x;
	double	oldplane_x;
	double	rot_speed;

	olddir_x = data->game.player.dir_x;
	oldplane_x = data->game.player.plane_x;
	rot_speed = ROT_SPEED;
	if (data->game.keys[KEY_LEFT])
		rot_speed = -ROT_SPEED;
	else if ((data->game.keys[KEY_LEFT] && data->game.keys[KEY_RIGHT])
		|| (!data->game.keys[KEY_LEFT] && !data->game.keys[KEY_RIGHT]))
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
