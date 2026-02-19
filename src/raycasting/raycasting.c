/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:00:27 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/19 18:17:23 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	load_wall_textures(t_data *data)
{
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

int	get_texture_color(t_img *img, int x, int y)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length) + (x * (game->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_textured_line(t_game *game, int x, int draw_start, int draw_end,
		t_img *img, int img_x, int line_height)
{
	int		y;
	double	step;
	double	tex_pos;
	int		img_y;
	int		color;

	step = (double)img->height / line_height;
	tex_pos = (draw_start - game->win_h / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		img_y = (int)tex_pos;
		if (img_y < 0)
			img_y = 0;
		if (img_y >= img->height)
			img_y = img->height - 1;
		tex_pos += step;
		color = get_texture_color(img, img_x, img_y);
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

// Faire structure pour raycasting

void	raycasting(t_game *game)
{
	t_raycasting_utils utils;
	int		x;
	int	line_height;

	x = 0;
	while (x < game->win_w)
	{
		calculate_ray_dir(&utils, game, x);
		// 2. dans quelle case de la map on est
		utils.map_x = (int)game->player.pos_x;
		utils.map_y = (int)game->player.pos_y;
		// 3. distance parcourue par le rayon pour aller d'une ligne x a la suivante
		utils.delta_dist_x = fabs(1 / utils.ray_dir_x); //1e30
		utils.delta_dist_y = fabs(1 / utils.ray_dir_y);
		
		dda(&utils, game);
		touch_wall(&utils, game);
		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
		if (utils.side == 0)
			utils.perp_wall_dist = utils.side_dist_x - utils.delta_dist_x;
		else
			utils.perp_wall_dist = utils.side_dist_y - utils.delta_dist_y;
		line_height = pixel_to_fill(&utils, game);
		//	calcul ou le rayon touche le wall
		line_height = pixel_to_fill(&utils, game);
		draw_textured_line(game, x, utils.draw_start, utils.draw_end, utils.img, convert_coords_textures(&utils, game), line_height);
		x++;
	}
}

void	get_texture(t_raycasting_utils *utils, t_game *game)
{
	//char wall_type;

	//wall_type = game->map.map[map_y][map_x];
	//if (wall_type == 'D')
	//	img = &game->door; // door texture
	if (utils->side == 0)
	{
		if (utils->ray_dir_x > 0)
			utils->img = &game->textures[3];
		else
			utils->img = &game->textures[2];
	}
	else
	{
		if (utils->ray_dir_y > 0)
			utils->img = &game->textures[1];
		else
			utils->img = &game->textures[0];
	}
}
