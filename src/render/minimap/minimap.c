/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:50:21 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:59:18 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	put_pixel_to_img(t_game *game, int *img_data, int line_len,
	t_pos pos, int color)
{
	int	x;
	int	y;

	x = pos.x;
	y = pos.y;
	if (x < 0 || x >= game->win_w || y < 0 || y >= game->win_h)
		return ;
	img_data[y * (line_len / 4) + x] = color;
}

void	draw_player_direction(t_game *game, int *img_data, int line_len, int x,
		int y)
{
	int		i;
	t_pos	pos;

	i = 0;
	while (i < 8)
	{
		pos.x = x + (int)(game->player.dir_x * i);
		pos.y = y + (int)(game->player.dir_y * i);
		put_pixel_to_img(game, img_data, line_len, pos, 0x00FF00);
		i++;
	}
}

void	print_player_pos(t_game *game, int *img_data, int line_len)
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
			put_pixel_to_img(game, img_data, line_len,
				(t_pos){(int)(game->player.pos_x * MINI_TILE) + i,
				(int)(game->player.pos_y * MINI_TILE) + j}, color);
			j++;
		}
		i++;
	}
	draw_player_direction(game, img_data, line_len,
		(int)(game->player.pos_x * MINI_TILE),
		(int)(game->player.pos_y * MINI_TILE));
}

void	draw_minimap(t_game *game)
{
	t_mini mini;
	int	color;
	int	*img_data;

	img_data = (int *)mlx_get_data_addr(game->img, &mini.bpp, &mini.line_len, &mini.endian);
	if (!img_data)
		return ;
	mini.y = 0;
	while (mini.y < game->map.height * MINI_TILE)
	{
		mini.x = 0;
		while (mini.x < game->map.width * MINI_TILE)
		{
			if (game->map.map[mini.y / MINI_TILE][mini.x / MINI_TILE] == '1'
				|| game->map.map[mini.y / MINI_TILE][mini.x / MINI_TILE] == 'D')
				color = WALL_COLOR;
			else
				color = FLOOR_COLOR;
			put_pixel_to_img(game, img_data, mini.line_len,
					(t_pos){mini.x, mini.y}, color);
			mini.x++;
		}
		mini.y++;
	}
	print_player_pos(game, img_data, mini.line_len);
}
