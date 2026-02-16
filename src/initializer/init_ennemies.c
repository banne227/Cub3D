/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ennemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:48:03 by banne             #+#    #+#             */
/*   Updated: 2026/02/16 16:13:00 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int count_ennemies(char **map)
{
	int count;
	int x;
	int y;

	if (!map)
		return (0);
	count = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

t_pos get_ennemy_pos(char **map, int index)
{
	int count;
	int x;
	int y;

	if (!map)
		return ((t_pos){-1, -1});
	count = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'E')
			{
				if (count == index)
					return ((t_pos){x, y});
				count++;
			}
			x++;
		}
		y++;
	}
	return ((t_pos){-1, -1});
}

void upload_ennemy_texture(void *mlx, void *img[4])
{
	img[0] = load(mlx, "textures/ennemies/walk.xpm");
	img[1] = load(mlx, "textures/ennemies/shoot.xpm");
	img[2] = load(mlx, "textures/ennemies/hit.xpm");
	img[3] = load(mlx, "textures/ennemies/dead.xpm");
}

t_ennemy *init_ennemies(char **map, void *mlx)
{
	t_ennemy *ennemies;
	int count;
	int i;

	count = count_ennemies(map);
	if (count == 0)
		return (NULL);
	ennemies = malloc(sizeof(t_ennemy) * count);
	if (!ennemies)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ennemies[i].pos = get_ennemy_pos(map, i);
		ennemies[i].health = 100;
		ennemies[i].alive = true;
		upload_ennemy_texture(mlx, ennemies[i].img);
		i++;
	}
	return (ennemies);
}