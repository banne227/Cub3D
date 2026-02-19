/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 08:18:24 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:39:23 by banne            ###   ########.fr       */
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

void	init_screen(t_data *data)
{
	data->screen = (t_img *)malloc(sizeof(t_img));
	if (!data->screen)
		data->error = true;
	else
	{
		data->screen->img = NULL;
		data->screen->addr = NULL;
		data->screen->width = 0;
		data->screen->height = 0;
		data->screen->bits_per_pixel = 0;
		data->screen->line_length = 0;
		data->screen->endian = 0;
	}
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
	data.start_map_index = -1;
	data.error = false;
	init_screen(&data);
	data.game.mlx = mlx_init();
	if (!data.game.mlx)
	{
		data.error = true;
		return (data);
	}
	data.game.win = mlx_new_window(data.game.mlx, WIN_W, WIN_H, "CUB3D");
	if (!data.game.win)
		data.error = true;
	return (data);
}

t_data	init_data_with_weapons(t_data *data)
{
	t_player	parsed_player;

	parsed_player = data->game.player;
	data->game = init_game();
	data->game.floor_color = rgb_to_int(data->text_path[F]);
	data->game.ceiling_color = rgb_to_int(data->text_path[C]);
	data->game.player = parsed_player;
	if (!data->game.mlx || !data->game.win)
	{
		data->error = true;
		return (*data);
	}
	init_weapon(data->game.mlx);
	data->game.ennemys = init_ennemies(data->map.map, data->game.mlx);
	return (*data);
}
