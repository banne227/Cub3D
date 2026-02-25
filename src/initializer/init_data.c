/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 08:18:24 by banne             #+#    #+#             */
/*   Updated: 2026/02/25 15:26:48 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

	ft_memset(&data, 0, sizeof(t_data));
	i = 0;
	while (i < 6)
	{
		data.text_path[i] = NULL;
		i++;
	}
	data.anim.enter_frame = 0;
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
	return (data.game.img = NULL, data);
}

t_data	init_data_with_weapons(t_data *data)
{
	t_player	parsed_player;
	void		*mlx_tmp;
	void		*win_tmp;

	parsed_player = data->game.player;
	mlx_tmp = data->game.mlx;
	win_tmp = data->game.win;
	data->game = init_game();
	data->game.mlx = mlx_tmp;
	data->game.win = win_tmp;
	data->game.floor_color = rgb_to_int(data->text_path[F]);
	data->game.ceiling_color = rgb_to_int(data->text_path[C]);
	data->game.player = parsed_player;
	if (!data->game.mlx || !data->game.win)
	{
		data->error = true;
		return (*data);
	}
	data->game.weapon = init_weapon(data->game.mlx);
	return (*data);
}
