/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 15:22:56 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/25 15:26:18 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	free_texture(t_game *game, t_img *texture)
{
	if (texture->img)
	{
		mlx_destroy_image(game->mlx, texture->img);
		texture->img = NULL;
		texture->addr = NULL;
	}
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i <= 4)
	{
		free_texture(game, &game->textures[i]);
		i++;
	}
}
