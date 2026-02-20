/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:00:27 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/20 14:37:18 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

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

void	draw_textured_line(t_game *game, int x,
		t_raycasting_utils *utils, int img_x)
{
	int		y;
	double	step;
	double	tex_pos;
	int		img_y;
	int		color;

	step = (double)utils->img->height
		/ utils->line_height;
	tex_pos = (utils->draw_start - game->win_h
			/ 2 + utils->line_height / 2) * step;
	y = utils->draw_start;
	while (y < utils->draw_end)
	{
		img_y = (int)tex_pos;
		if (img_y < 0)
			img_y = 0;
		if (img_y >= utils->img->height)
			img_y = utils->img->height - 1;
		tex_pos += step;
		color = get_texture_color(utils->img, img_x, img_y);
		my_mlx_pixel_put(game, x, y, color);
		y++;
	}
}

static void	get_texture(t_raycasting_utils *utils, t_game *game)
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

void	raycasting(t_game *game)
{
	t_raycasting_utils	utils;
	int					x;

	x = 0;
	while (x < game->win_w)
	{
		calculate_ray_dir(&utils, game, x);
		utils.map_x = (int)game->player.pos_x;
		utils.map_y = (int)game->player.pos_y;
		utils.delta_dist_x = fabs(1 / utils.ray_dir_x);
		utils.delta_dist_y = fabs(1 / utils.ray_dir_y);
		dda(&utils, game);
		touch_wall(&utils, game);
		if (utils.side == 0)
			utils.perp_wall_dist = utils.side_dist_x - utils.delta_dist_x;
		else
			utils.perp_wall_dist = utils.side_dist_y - utils.delta_dist_y;
		utils.line_height = pixel_to_fill(&utils, game);
		utils.line_height = pixel_to_fill(&utils, game);
		get_texture(&utils, game);
		draw_textured_line(game, x, &utils,
			convert_coords_textures(&utils, game));
		x++;
	}
}
