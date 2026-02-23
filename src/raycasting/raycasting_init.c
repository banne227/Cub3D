/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 13:39:35 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/23 12:44:36 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static void	load_door(t_data *data)
{
	data->game.textures[4].img = mlx_xpm_file_to_image(data->game.mlx,
													   "./textures/block/door.xpm", &data->game.textures[4].width,
													   &data->game.textures[4].height);
	if (!data->game.textures[4].img)
	{
		printf("Error: Failed to load east texture\n");
		close_game(data);
	}
	data->game.textures[4].addr = mlx_get_data_addr(data->game.textures[4].img,
													&data->game.textures[4].bits_per_pixel,
													&data->game.textures[4].line_length,
													&data->game.textures[4].endian);
}

static void load_wall_textures1(t_data *data)
{
	load_door(data);
	data->game.textures[0].img = mlx_xpm_file_to_image(data->game.mlx,
													   data->text_path[NORTH], &data->game.textures[0].width,
													   &data->game.textures[0].height);
	if (!data->game.textures[0].img)
	{
		printf("Error: Failed to load north texture\n");
		close_game(data);
	}
	data->game.textures[0].addr = mlx_get_data_addr(data->game.textures[0].img,
													&data->game.textures[0].bits_per_pixel,
													&data->game.textures[0].line_length,
													&data->game.textures[0].endian);
	data->game.textures[1].img = mlx_xpm_file_to_image(data->game.mlx,
													   data->text_path[SOUTH], &data->game.textures[1].width,
													   &data->game.textures[1].height);
	if (!data->game.textures[1].img)
	{
		printf("Error: Failed to load south texture\n");
		close_game(data);
	}
	data->game.textures[1].addr = mlx_get_data_addr(data->game.textures[1].img,
													&data->game.textures[1].bits_per_pixel,
													&data->game.textures[1].line_length,
													&data->game.textures[1].endian);
}

void load_wall_textures(t_data *data)
{
	load_wall_textures1(data);
	data->game.textures[2].img = mlx_xpm_file_to_image(data->game.mlx,
													   data->text_path[WEST], &data->game.textures[2].width,
													   &data->game.textures[2].height);
	if (!data->game.textures[2].img)
	{
		printf("Error: Failed to load west texture\n");
		close_game(data);
	}
	data->game.textures[2].addr = mlx_get_data_addr(data->game.textures[2].img,
													&data->game.textures[2].bits_per_pixel,
													&data->game.textures[2].line_length,
													&data->game.textures[2].endian);
	data->game.textures[3].img = mlx_xpm_file_to_image(data->game.mlx,
													   data->text_path[EAST], &data->game.textures[3].width,
													   &data->game.textures[3].height);
	if (!data->game.textures[3].img)
	{
		printf("Error: Failed to load east texture\n");
		close_game(data);
	}
	data->game.textures[3].addr = mlx_get_data_addr(data->game.textures[3].img,
													&data->game.textures[3].bits_per_pixel,
													&data->game.textures[3].line_length,
													&data->game.textures[3].endian);
}

