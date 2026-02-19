/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   needed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 08:32:01 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 12:41:38 by banne            ###   ########.fr       */
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

bool is_wall(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height)
		return (0);
	return (game->map.map[y][x] == '1' || game->map.map[y][x] == 'D');
}
