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

void	render_pixel(t_game *game, int x, int *y, int color)
{
	if (color != 0x000000)
		my_mlx_pixel_put(game, x, *y, color);
	(*y)++;
}

static void	draw_sprite_stripe(t_game *game, t_sprite_utils *utils, int x)
{
	int		y;
	double	step;
	double	tex_pos;
	t_pos	img_pos;
	int		color;

	if (x < 0 || x >= game->win_w || utils->transform_y <= 0
		|| utils->transform_y >= game->z_buffer[x])
		return ;
	img_pos.x = get_sprite_tex_x(utils, x);
	step = (double)utils->img->height / utils->line_height;
	tex_pos = (utils->draw_start - game->win_h
			/ 2 + utils->line_height / 2) * step;
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

static void	spritecast_one(t_game *game, t_ennemy *e)
{
	t_sprite_utils	utils;
	t_img			sprite_img;
	int				x;

	if (!e || !e->display || !game->z_buffer)
		return ;
	calculate_transform(game, e, &utils);
	if (utils.transform_y <= 0.01)
		return ;
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

void	render_ennemies(t_game *game)
{
	t_ennemy	*e;

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
