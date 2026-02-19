/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sky_n_floor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 17:27:23 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/19 13:32:55 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	print_sky_n_floor(t_data *data)
{
	int	x;
	int	y;

	// utiliser data->game a la place de data->screen
	y = 0;
	// data->screen->img = mlx_new_image(data->game.mlx, data->game.win_w,
			//data->game.win_h);
	data->game.addr = mlx_get_data_addr(data->game.img,
			&data->game.bits_per_pixel, &data->game.line_length,
			&data->game.endian);
	y = 0;
	while (y < data->game.win_h / 2)
	{
		x = 0;
		while (x < data->game.win_w)
		{
			my_mlx_pixel_put(&data->game, x, y, data->game.ceiling_color);
			x++;
		}
		y++;
	}
	y = data->game.win_h / 2;
	while (y < data->game.win_h)
	{
		x = 0;
		while (x < data->game.win_w)
		{
			my_mlx_pixel_put(&data->game, x, y, data->game.floor_color);
			x++;
		}
		y++;
	}
}
