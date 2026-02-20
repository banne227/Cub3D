/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:39:35 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/20 14:35:48 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	load_wall_textures1(t_data *data)
{
	data->game.textures[0].img = mlx_xpm_file_to_image(data->game.mlx,
			data->text_path[NORTH], &data->game.textures[0].width,
			&data->game.textures[0].height);
	data->game.textures[0].addr = mlx_get_data_addr(data->game.textures[0].img,
			&data->game.textures[0].bits_per_pixel,
			&data->game.textures[0].line_length,
			&data->game.textures[0].endian);
	data->game.textures[1].img = mlx_xpm_file_to_image(data->game.mlx,
			data->text_path[SOUTH], &data->game.textures[1].width,
			&data->game.textures[1].height);
	data->game.textures[1].addr = mlx_get_data_addr(data->game.textures[1].img,
			&data->game.textures[1].bits_per_pixel,
			&data->game.textures[1].line_length,
			&data->game.textures[1].endian);
}

void	load_wall_textures(t_data *data)
{
	load_wall_textures1(data);
	data->game.textures[2].img = mlx_xpm_file_to_image(data->game.mlx,
			data->text_path[WEST], &data->game.textures[2].width,
			&data->game.textures[2].height);
	data->game.textures[2].addr = mlx_get_data_addr(data->game.textures[2].img,
			&data->game.textures[2].bits_per_pixel,
			&data->game.textures[2].line_length,
			&data->game.textures[2].endian);
	data->game.textures[3].img = mlx_xpm_file_to_image(data->game.mlx,
			data->text_path[EAST], &data->game.textures[3].width,
			&data->game.textures[3].height);
	data->game.textures[3].addr = mlx_get_data_addr(data->game.textures[3].img,
			&data->game.textures[3].bits_per_pixel,
			&data->game.textures[3].line_length,
			&data->game.textures[3].endian);
}
