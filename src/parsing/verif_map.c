/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 09:15:17 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 10:58:30 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	print_pos_error(int x, int y)
{
	ft_printf("Error\nInvalid position at (%d, %d)\n", x, y);
	return (false);
}

static bool	map_is_closed(char **map, int width, int height)
{
	int	x;
	int	y;

	y = 0;
	if (!map)
		return (false);
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W'
				|| map[y][x] == 'D' || map[y][x] == 'M')
			{
				if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
					return (print_pos_error(x, y));
				if (map[y - 1][x] == 'V' || map[y + 1][x] == 'V' || map[y][x
					- 1] == 'V' || map[y][x + 1] == 'V')
					return (print_pos_error(x, y));
			}
			x++;
		}
		y++;
	}
	return (true);
}

static bool	have_valid_chars(char **map)
{
	int	x;
	int	y;

	y = 0;
	if (!map)
		return (false);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'V'
				&& map[y][x] != 'N' && map[y][x] != 'S' && map[y][x] != 'E'
				&& map[y][x] != 'W' && map[y][x] != 'D' && map[y][x] != 'M')
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}

static bool	only_one_player(char **map, t_data *data)
{
	int	x;
	int	y;
	int	player_count;

	y = 0;
	player_count = 0;
	if (!map)
		return (false);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E'
				|| map[y][x] == 'W')
			{
				data->game.player.pos_x = x + 0.5;
				data->game.player.pos_y = y + 0.5;
				update_player_data(data, map[y][x]);
				player_count++;
			}
			x++;
		}
		y++;
	}
	return (player_count == 1);
}

bool	map_valid(t_data *data)
{
	if (!data->map.map || data->map.width <= 0 || data->map.height <= 0)
		return (false);
	if (data->map.map[0] == NULL)
		return (false);
	if (!map_is_closed(data->map.map, data->map.width, data->map.height))
	{
		ft_printf("Map isn't closed\n");
		return (false);
	}
	if (!have_valid_chars(data->map.map))
	{
		ft_printf("Error\nMap contains invalid characters\n");
		return (false);
	}
	if (!only_one_player(data->map.map, data))
	{
		ft_printf("Error\nMap must contain exactly one player start position\n");
		return (false);
	}
	return (true);
}
