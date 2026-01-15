/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 08:18:24 by banne             #+#    #+#             */
/*   Updated: 2026/01/15 08:31:11 by banne            ###   ########.fr       */
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
	game.win_w = 800;
	game.win_h = 600;
	game.posX = 0.0;
	game.posY = 0.0;
	game.dirX = 0.0;
	game.dirY = 0.0;
	game.planeX = 0.0;
	game.planeY = 0.0;
	game.floor_color = 0;
	game.ceiling_color = 0;
	if (!init_mlx(&game))
		printf("Error\nFailed to initialize game graphics\n");
	return (game);
}

t_data init_data(void)
{
	t_data data;
	
	data.no = NULL;
	data.so = NULL;
	data.we = NULL;
	data.ea = NULL;
	data.f = NULL;
	data.c = NULL;
	data.map = init_map();
	data.game = init_game();
	data.start_map_index = -1;
	data.error = false;
	if (!data.game.mlx || !data.game.win)
		data.error = true;
	return (data);
}

