/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ennemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:48:03 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 13:59:46 by banne            ###   ########.fr       */
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
			if (map[y][x] == 'M')
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
			if (map[y][x] == 'M')
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
	int x;
	int y;

	img[0] = mlx_xpm_file_to_image(mlx, "textures/ennemies/walk.xpm", &x, &y);
	img[1] = mlx_xpm_file_to_image(mlx, "textures/ennemies/shoot1.xpm", &x, &y);
	img[2] = mlx_xpm_file_to_image(mlx, "textures/ennemies/hit.xpm", &x, &y);
	img[3] = mlx_xpm_file_to_image(mlx, "textures/ennemies/dead.xpm", &x, &y);
}

t_ennemy *init_ennemies(char **map, void *mlx)
{
	t_ennemy *ennemies;
	int count;
	int i;

	if (!map || !mlx)
		return (NULL);
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
		ennemies[i].display = ennemies[i].img[1];
		if (!ennemies[i].display)
			ennemies[i].display = ennemies[i].img[0];
		ennemies[i].frame = 0;
		ennemies[i].hit_frame = 0;
		ennemies[i].next = NULL;
		if (i < count - 1)
			ennemies[i].next = &ennemies[i + 1];
		i++;
	}
	return (ennemies);
}
