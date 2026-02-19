/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 08:32:01 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 12:51:30 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void open_door(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return;
	if (!is_door(map, x, y))
		return;
	if (map->map[y][x] == 'D')
		map->map[y][x] = 'd';
	else if (map->map[y][x] == 'd')
		map->map[y][x] = 'D';
}

bool is_door(t_map *map, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	return (map->map[y][x] == 'D' || map->map[y][x] == 'd');
}

int mround(double value)
{
	if (value < 0)
		return ((int)(value - 0.6));
	else
		return ((int)(value + 0.6));
}

bool is_wall(t_map *map, double x, double y)
{
	int map_x = mround(x);
	int map_y = mround(y);
	if (map_x < 0 || map_x >= map->width || map_y < 0 || map_y >= map->height)
		return (0);
	return (map->map[map_y][map_x] == '1' || map->map[map_y][map_x] == 'D');
}
