/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 08:18:24 by banne             #+#    #+#             */
/*   Updated: 2026/02/10 15:47:22 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_text	init_text(void)
{
	t_text	text;

	text.no = NULL;
	text.so = NULL;
	text.we = NULL;
	text.ea = NULL;
	text.f = NULL;
	text.c = NULL;
	return (text);
}

t_map	init_map(void)
{
	t_map	map;

	map.map = NULL;
	map.width = 0;
	map.height = 0;
	return (map);
}

t_player	init_player(void)
{
	t_player	player;

	player.posX = 0.0;
	player.posY = 0.0;
	player.dirX = 0.0;
	player.dirY = 0.0;
	player.planeX = 0.0;
	player.planeY = 0.0;
	return (player);
}

t_enter	init_enter(void)
{
	t_enter	enter;

	enter.ent1 = NULL;
	enter.ent2 = NULL;
	enter.ent3 = NULL;
	enter.ent4 = NULL;
	enter.ent5 = NULL;
	enter.ent6 = NULL;
	enter.ent7 = NULL;
	enter.ent8 = NULL;
	enter.ent9 = NULL;
	return (enter);
}

t_game	init_game(void)
{
	t_game	game;

	game.mlx = NULL;
	game.win = NULL;
	game.img = NULL;
	game.map = init_map();
	game.win_w = WIN_W;
	game.win_h = WIN_H;
	game.player = init_player();
	game.floor_color = 0;
	game.ceiling_color = 0;
	game.state = STATE_MENU;
	game.last_key = 0;
	game.menu_option = 0;
	game.enter = init_enter();
	if (!init_mlx(&game))
		printf("Error\nFailed to initialize game graphics\n");
	return (game);
}

t_data	init_data(void)
{
	t_data	data;
	int		i;

	i = 0;
	while (i < 6)
	{
		data.text_path[i] = NULL;
		i++;
	}
	data.tex = init_text();
	data.map = init_map();
	data.game = init_game();
	data.start_map_index = -1;
	data.error = false;
	if (!data.game.mlx || !data.game.win)
		data.error = true;
	return (data);
}

void	update_player_data(t_data *data, char d)
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