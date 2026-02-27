/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 12:54:02 by banne             #+#    #+#             */
/*   Updated: 2026/02/27 13:32:01 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**make_copy_grid(t_map *map)
{
	int		i;
	char	**copy;

	if (!map || !map->map)
		return (NULL);
	copy = malloc(sizeof(char *) * (map->height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		copy[i] = malloc(sizeof(char) * (map->width + 1));
		if (!copy[i])
		{
			free_tab(copy);
			return (NULL);
		}
		ft_strlcpy(copy[i], map->map[i], map->width + 1);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	flood_fill(t_map *map, char **grid, int x, int y)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	if (grid[y][x] == ' ')
		return (0);
	if (grid[y][x] == '1' || grid[y][x] == 'V')
		return (1);
	grid[y][x] = 'V';
	if (!flood_fill(map, grid, x + 1, y))
		return (0);
	if (!flood_fill(map, grid, x - 1, y))
		return (0);
	if (!flood_fill(map, grid, x, y + 1))
		return (0);
	if (!flood_fill(map, grid, x, y - 1))
		return (0);
	return (1);
}

//static int	verif_access(char **grid, int width, int height)
//{
//	int	x;
//	int	y;

//	if (!grid)
//		return (0);
//	y = 0;
//	while (y < height)
//	{
//		x = 0;
//		while (x < width)
//		{
//			if (grid[y][x] == 'M')
//			{
//				ft_printf("Error\nUnreachable ennemy at (%d, %d)\n", x, y);
//				return (0);
//			}
//			x++;
//		}
//		y++;
//	}
//	return (1);
//}

static int	get_player_pos(t_map *map, t_game *game)
{
	int		i;
	int		j;

	if (!game || !map || !map->map)
		return (0);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				game->player.pos_x = j;
				game->player.pos_y = i;
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	all_accessible(t_map *map, t_game *game)
{
	int		x;
	int		y;
	char	**copy;
	int		closed;

	if (!map || !map->map || !game)
		return (0);
	if (!get_player_pos(map, game))
		return (0);
	x = game->player.pos_x;
	y = game->player.pos_y;
	copy = make_copy_grid(map);
	if (!copy)
		return (0);
	closed = flood_fill(map, copy, x, y);
	free_tab(copy);
	if (closed == 0)
		printf("Map not closed\n");
	return (closed);
}
