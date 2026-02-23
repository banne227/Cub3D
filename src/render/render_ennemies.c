/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_ennemies.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 08:45:21 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 08:45:21 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void calculate_transform(t_game *game, t_ennemy *e,
								t_sprite_utils *utils)
{
	double rel_x;
	double rel_y;
	double inv_det;

	rel_x = e->pos.x + 0.5 - game->player.pos_x;
	rel_y = e->pos.y + 0.5 - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y - game->player.dir_x * game->player.plane_y);
	utils->transform_x = inv_det * (game->player.dir_y * rel_x - game->player.dir_x * rel_y);
	utils->transform_y = inv_det * (-game->player.plane_y * rel_x + game->player.plane_x * rel_y);
}

static t_img create_sprite_img(void *mlx_img)
{
	t_img img;

	img.img = mlx_img;
	img.addr = mlx_get_data_addr(mlx_img, &img.bits_per_pixel,
								 &img.line_length, &img.endian);
	img.width = 128;
	img.height = 128;
	return (img);
}

static int calculate_dimensions(t_sprite_utils *sprite,
								t_game *game)
{
	t_raycasting_utils utils;

	utils.perp_wall_dist = sprite->transform_y;
	sprite->line_height = pixel_to_fill(&utils, game);
	sprite->draw_start = utils.draw_start;
	sprite->draw_end = utils.draw_end;
	sprite->sprite_screen_x = (int)((game->win_w / 2.0) * (1 + sprite->transform_x / sprite->transform_y));
	sprite->draw_start_x = -sprite->line_height / 2 + sprite->sprite_screen_x;
	sprite->draw_end_x = sprite->line_height / 2 + sprite->sprite_screen_x;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	if (sprite->draw_end_x >= game->win_w)
		sprite->draw_end_x = game->win_w - 1;
	return (sprite->line_height);
}

static int get_sprite_tex_x(t_sprite_utils *sprite, int x)
{
	int img_x;
	int sprite_left;

	sprite_left = -sprite->line_height / 2 + sprite->sprite_screen_x;
	img_x = (int)((x - sprite_left) * sprite->img->width / (double)sprite->line_height);
	if (img_x < 0)
		img_x = 0;
	if (img_x >= sprite->img->width)
		img_x = sprite->img->width - 1;
	return (img_x);
}

static void render_pixel(t_game *game, int x, int *y, int color)
{
	if (color != 0x000000)
		my_mlx_pixel_put(game, x, *y, color);
	(*y)++;
}

static void draw_sprite_stripe(t_game *game, t_sprite_utils *utils, int x)
{
	int y;
	double step;
	double tex_pos;
	t_pos img_pos;
	int color;

	if (x < 0 || x >= game->win_w || utils->transform_y <= 0 || utils->transform_y >= game->z_buffer[x])
		return;
	img_pos.x = get_sprite_tex_x(utils, x);
	step = (double)utils->img->height / utils->line_height;
	tex_pos = (utils->draw_start - game->win_h / 2 + utils->line_height / 2) * step;
	y = utils->draw_start;
	while (y < utils->draw_end)
	{
		img_pos.y = (int)tex_pos;
		if (img_pos.y < 0)
			img_pos.y = 0;
		if (img_pos.y >= utils->img->height)
			img_pos.y = utils->img->height - 1;
		tex_pos += step;
		color = get_texture_color(utils->img, img_pos.x, img_pos.y);
		render_pixel(game, x, &y, color);
	}
}

static void spritecast_one(t_game *game, t_ennemy *e)
{
	t_sprite_utils utils;
	t_img sprite_img;
	int x;

	if (!e || !e->display || !game->z_buffer)
		return;
	calculate_transform(game, e, &utils);
	if (utils.transform_y <= 0.01)
		return;
	sprite_img = create_sprite_img(e->display);
	utils.img = &sprite_img;
	calculate_dimensions(&utils, game);
	x = utils.draw_start_x;
	while (x < utils.draw_end_x)
	{
		draw_sprite_stripe(game, &utils, x);
		x++;
	}
}

void render_ennemies(t_game *game)
{
	t_ennemy *e;

	e = game->ennemys;
	while (e)
	{
		if (e->alive)
		{
			if (e->hit_frame > 0)
			{
				e->display = e->img[2];
				e->hit_frame--;
			}
			else
			{
				e->display = e->img[1];
			}
		}
		else
		{
			e->display = e->img[3];
		}
		spritecast_one(game, e);
		e = e->next;
	}
}
