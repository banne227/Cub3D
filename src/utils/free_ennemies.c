/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ennemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 11:05:40 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 11:10:56 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void free_ennemies(t_ennemy *ennemies, void *mlx, int count)
{
	int i;
	int j;

	if (!ennemies)
		return;
	i = 0;
	while (i < count)
	{
		j = 0;
		while (j < 4)
		{
			if (ennemies[i].img[j])
				mlx_destroy_image(mlx, ennemies[i].img[j]);
			j++;
		}
		i++;
	}
	free(ennemies);
}