/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 17:49:53 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:51:54 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fade_display_img(t_data *data, void *img, int opacity)
{
	char			*addr;
	unsigned int	pixel;
	int				x, y, bits, line_len, endian;

	if (!img || !data->game.mlx || !data->game.win)
		return ;
	addr = mlx_get_data_addr(img, &bits, &line_len, &endian);
	y = 0;
	while (y < 512)
	{
		x = 0;
		while (x < 512)
		{
			pixel = *(unsigned int *)(addr + y * line_len + x * 4);
			pixel = (pixel & 0xFFFFFF) | ((unsigned int)(opacity) << 24);
			*(unsigned int *)(addr + y * line_len + x * 4) = pixel;
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->game.mlx, data->game.win, img, 0, 0);
	data->anim.last_img = img;
}

void	display_img(t_data *data, void *img)
{
	int	h;
	int	w;

	if (!img || !data->game.mlx || !data->game.win)
		return ;
	h = 0;
	w = 0;
	if (data->anim.last_img != img)
	{
		mlx_clear_window(data->game.mlx, data->game.win);
		printf("Displaying image %p\n", img);
	}
	mlx_put_image_to_window(data->game.mlx, data->game.win, img, w, h);
	data->anim.last_img = img;
}

void	load_enter(void *mlx, t_anim *enter)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	enter->ent[0] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter0.xpm",
			&w, &h);
	enter->ent[1] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter1.xpm",
			&w, &h);
	enter->ent[2] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter2.xpm",
			&w, &h);
	enter->ent[3] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter3.xpm",
			&w, &h);
	enter->ent[4] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter4.xpm",
			&w, &h);
	enter->ent[5] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter5.xpm",
			&w, &h);
	enter->ent[6] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter6.xpm",
			&w, &h);
	enter->ent[7] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter7.xpm",
			&w, &h);
	enter->ent[8] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter8.xpm",
			&w, &h);
	enter->ent[9] = mlx_xpm_file_to_image(mlx, "textures/menu/enter/enter9.xpm",
			&w, &h);
}

void	destroy_enter(t_data *data)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (data->anim.ent[i])
			destroy_img(data->game.mlx, data->anim.ent[i]);
		i++;
	}
}

void	init_anim(t_data *data)
{
	load_enter(data->game.mlx, &data->anim);
	data->anim.last_frame_time = timestamp();
}

void	display_enter(t_data *data)
{
	int	elapsed;
	int	opacity;

	if (data->anim.enter_frame > 9)
	{
		destroy_enter(data);
		data->game.state = STATE_PLAY;
		data->game.menu_option = 0;
		return ;
	}
	elapsed = timestamp() - data->anim.last_frame_time;
	if (elapsed < 50)
		opacity = (elapsed * 255) / 50;
	else if (elapsed < 125)
		opacity = 255;
	else
		opacity = 255 - (((elapsed - 125) * 255) / 50);
	fade_display_img(data, data->anim.ent[data->anim.enter_frame], opacity);
	if (elapsed > 150)
	{
		data->anim.enter_frame++;
		data->anim.last_frame_time = timestamp();
	}
}
