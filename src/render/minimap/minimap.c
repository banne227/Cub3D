/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:50:21 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 16:50:28 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	put_pixel_to_img(t_game *game, int x, int y, int color)
{
	int	*img_data;
	int	bpp;
	int	line_len;
	int	endian;

	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return ;
	img_data = (int *)mlx_get_data_addr(game->img, &bpp, &line_len, &endian);
	img_data[y * (line_len / 4) + x] = color;
}

void	draw_player_direction(t_game *game, int x, int y)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		put_pixel_to_img(game, x + (int)(game->player.dirX * i), y
			+ (int)(game->player.dirY * i), 0x00FF00);
		i++;
	}
}

void	print_player_pos(t_game *game, int x, int y)
{
	int	color;
	int	i;
	int	j;
	int	size;

	color = 0xFF0000;
	size = 3;
	i = -size;
	while (i <= size)
	{
		j = -size;
		while (j <= size)
		{
			put_pixel_to_img(game, x + j, y + i, color);
			j++;
		}
		i++;
	}
	draw_player_direction(game, x, y);
}

void	draw_minimap(t_game *game)
{
	int x;
	int y;
	int color;

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
			put_pixel_to_img(game, x, y, color);
			x++;
		}
		y++;
	}
	print_player_pos(game, (int)(game->player.posX * MINI_TILE),
		(int)(game->player.posY * MINI_TILE));
}