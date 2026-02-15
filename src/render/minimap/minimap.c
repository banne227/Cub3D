/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:50:21 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 17:05:05 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void put_pixel_to_img(t_game *game, int *img_data, int line_len,
							 int x, int y, int color)
{
	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return;
	img_data[y * (line_len / 4) + x] = color;
}

void draw_player_direction(t_game *game, int *img_data, int line_len,
						   int x, int y)
{
	int i;

	i = 0;
	while (i < 8)
	{
		put_pixel_to_img(game, img_data, line_len, x + (int)(game->player.dir_x * i), y + (int)(game->player.dir_y * i), 0x00FF00);
		i++;
	}
}

void print_player_pos(t_game *game, int *img_data, int line_len,
					  int x, int y)
{
	int color;
	int i;
	int j;
	int size;

	color = 0xFF0000;
	size = 3;
	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			put_pixel_to_img(game, img_data, line_len, x + j, y + i, color);
			j++;
		}
		i++;
	}
	draw_player_direction(game, img_data, line_len, x, y);
}

void draw_minimap(t_game *game)
{
	int x;
	int y;
	int color;
	int *img_data;
	int bpp;
	int line_len;
	int endian;

	img_data = (int *)mlx_get_data_addr(game->img, &bpp, &line_len, &endian);
	if (!img_data)
		return;

	y = 0;
	while (y < game->map.height * MINI_TILE)
	{
		x = 0;
		while (x < game->map.width * MINI_TILE)
		{
			if (game->map.map[y / MINI_TILE][x / MINI_TILE] == '1')
				color = WALL_COLOR;
			else
				color = FLOOR_COLOR;
			put_pixel_to_img(game, img_data, line_len, x, y, color);
			x++;
		}
		y++;
	}
	print_player_pos(game, img_data, line_len,
					 (int)(game->player.pos_x * MINI_TILE),
					 (int)(game->player.pos_y * MINI_TILE));
}