/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 08:18:24 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 17:18:01 by banne            ###   ########.fr       */
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

	player.pos_x = 0.0;
	player.pos_y = 0.0;
	player.dir_x = 0.0;
	player.dir_y = 0.0;
	player.plane_x = 0.0;
	player.plane_y = 0.0;
	return (player);
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
	game.music_pid = 0;
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
	data.anim.enter_frame = 0;
	data.tex = init_text();
	data.map = init_map();
	data.game = init_game();
	data.start_map_index = -1;
	data.error = false;
	if (!data.game.mlx || !data.game.win)
		data.error = true;
	return (data);
}
