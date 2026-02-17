/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 08:29:55 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 17:18:25 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void *load(t_game *game, char *path)
{
	void *img;

	img = mlx_xpm_file_to_image(game->mlx, path, &game->win_w, &game->win_h);
	if (!img)
	{
		ft_printf("Error\nFailed to create new image\n");
		return (NULL);
	}
	return (img);
}

bool check_loading(t_data *data, void *img, void **texture)
{
	if (!img)
	{
		ft_printf("Error\nFailed to load texture\n");
		data->error = true;
		return (false);
	}
	else
		*texture = img;
	return (true);
}

int load_textures(t_data *data)
{
	check_loading(data, load(&data->game, data->text_path[NORTH]),
				  &data->tex.no);
	check_loading(data, load(&data->game, data->text_path[SOUTH]),
				  &data->tex.so);
	check_loading(data, load(&data->game, data->text_path[WEST]), &data->tex.we);
	check_loading(data, load(&data->game, data->text_path[EAST]), &data->tex.ea);
	if (data->error)
	{
		// free_textures(data);
		return (1);
	}
	return (0);
}
