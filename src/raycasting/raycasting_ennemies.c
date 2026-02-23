/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_ennemies.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:19:54 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 13:23:45 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	calculate_transform(t_game *game, t_ennemy *e, t_sprite_utils *utils)
{
	double	rel_x;
	double	rel_y;
	double	inv_det;

	rel_x = e->pos.x + 0.5 - game->player.pos_x;
	rel_y = e->pos.y + 0.5 - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	utils->transform_x = inv_det * (game->player.dir_y * rel_x
			- game->player.dir_x * rel_y);
	utils->transform_y = inv_det * (-game->player.plane_y * rel_x
			+ game->player.plane_x * rel_y);
}

t_img	create_sprite_img(void *mlx_img)
{
	t_img	img;

	img.img = mlx_img;
	img.addr = mlx_get_data_addr(mlx_img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	img.width = 128;
	img.height = 128;
	return (img);
}

	int	calculate_dimensions(t_sprite_utils *sprite, t_game *game)
{
	t_raycasting_utils	utils;

	utils.perp_wall_dist = sprite->transform_y;
	sprite->line_height = pixel_to_fill(&utils, game);
	sprite->draw_start = utils.draw_start;
	sprite->draw_end = utils.draw_end;
	sprite->sprite_screen_x = (int)((game->win_w / 2.0)
			* (1 + sprite->transform_x / sprite->transform_y));
	sprite->draw_start_x = -sprite->line_height / 2 + sprite->sprite_screen_x;
	sprite->draw_end_x = sprite->line_height / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	if (sprite->draw_end_x >= game->win_w)
		sprite->draw_end_x = game->win_w - 1;
	return (sprite->line_height);
}

int	get_sprite_tex_x(t_sprite_utils *sprite, int x)
{
	int	img_x;
	int	sprite_left;

	sprite_left = -sprite->line_height / 2 + sprite->sprite_screen_x;
	img_x = (int)((x - sprite_left) * sprite->img->width
			/ (double)sprite->line_height);
	if (img_x < 0)
		img_x = 0;
	if (img_x >= sprite->img->width)
		img_x = sprite->img->width - 1;
	return (img_x);
}
