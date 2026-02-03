/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 08:18:24 by banne             #+#    #+#             */
/*   Updated: 2026/02/03 08:23:31 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_map init_map(void)
{
	t_map map;

	map.map = NULL;
	map.width = 0;
	map.height = 0;
	return (map);
}
t_game init_game(void)
{
	t_game game;

	game.mlx = NULL;
	game.win = NULL;
	game.img = NULL;
	game.map = init_map();
	game.win_w = WIN_W;
	game.win_h = WIN_H;
	game.player.posX = 0.0;
	game.player.posY = 0.0;
	game.player.dirX = 0.0;
	game.player.dirY = 0.0;
	game.player.planeX = 0.0;
	game.player.planeY = 0.0;
	game.floor_color = 0;
	game.ceiling_color = 0;
	if (!init_mlx(&game))
		printf("Error\nFailed to initialize game graphics\n");
	return (game);
}

t_data init_data(void)
{
	t_data data;
	
	data.tex.NO = NULL;
	data.tex.SO = NULL;
	data.tex.WE = NULL;
	data.tex.EA = NULL;
	data.tex.F = NULL;
	data.tex.C = NULL;
	data.map = init_map();
	data.game = init_game();
	data.start_map_index = -1;
	data.error = false;
	if (!data.game.mlx || !data.game.win)
		data.error = true;
	return (data);
}

void update_player_data(t_data *data, char d)
{
	if (d == 'N')
	{
		data->game.player.dirX = 0;
		data->game.player.dirY = -1;
		data->game.player.planeX = 0.66;
		data->game.player.planeY = 0;
	}
	else if (d == 'S')
	{
		data->game.player.dirX = 0;
		data->game.player.dirY = 1;
		data->game.player.planeX = -0.66;
		data->game.player.planeY = 0;
	}
	else if (d == 'E')
	{
		data->game.player.dirX = 1;
		data->game.player.dirY = 0;
		data->game.player.planeX = 0;
		data->game.player.planeY = 0.66;
	}
	else if (d == 'W')
	{
		data->game.player.dirX = -1;
		data->game.player.dirY = 0;
		data->game.player.planeX = 0;
		data->game.player.planeY = -0.66;
	}
}