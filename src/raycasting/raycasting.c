/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 11:00:27 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/18 15:35:52 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void load_textures_raycast(t_data *data)
{
	data->game.textures[0]->img = data->tex.no;
	data->game.textures[0]->addr = mlx_get_data_addr(data->game.textures[0]->img,
										  &data->game.textures[0]->bits_per_pixel,
										  &data->game.textures[0]->line_length, &data->game.textures[0]->endian);
	data->game.textures[1]->img = data->tex.so;
	data->game.textures[1]->addr = mlx_get_data_addr(data->game.textures[1]->img,
										  &data->game.textures[1]->bits_per_pixel,
										  &data->game.textures[1]->line_length, &data->game.textures[1]->endian);
	data->game.textures[2]->img = data->tex.ea;
	data->game.textures[2]->addr = mlx_get_data_addr(data->game.textures[2]->img,
										  &data->game.textures[2]->bits_per_pixel,
										  &data->game.textures[2]->line_length, &data->game.textures[2]->endian);
	data->game.textures[3]->img = data->tex.we;
	data->game.textures[3]->addr = mlx_get_data_addr(data->game.textures[3]->img,
										  &data->game.textures[3]->bits_per_pixel,
										  &data->game.textures[3]->line_length, &data->game.textures[3]->endian);
}

int get_texture_color(t_img *img, int x, int y)
{
	char *dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return (0);
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char *dst;

	dst = game->addr + (y * game->line_length) + (x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void draw_textured_line(t_game *game, int x, int draw_start, int draw_end, t_img *img, int img_x)
{
	int	y;
	int line_height;
	double step;
	double img_pos;
	int img_y;
	int color;

	line_height = draw_end - draw_start;
	step = 1.0 * img->height / line_height;
	img_pos = (draw_start - game->win_h / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		img_y = (int)img_pos % img->height;
		color = get_texture_color(img, img_x, img_y);
		my_mlx_pixel_put(game, x, y, color);
		img_pos += step;
		y++;
	}
}

// void raycasting(t_game *game)
// {
// 	int x;
// 	double camera_x;
// 	double ray_dir_x;
// 	double ray_dir_y;
// 	int map_x;
// 	int map_y;
// 	double delta_dist_x;
// 	double delta_dist_y;
// 	int step_x;
// 	int step_y;
// 	double side_dist_x;
// 	double side_dist_y;
// 	int hit;
// 	double perp_wall_dist;
// 	int side;
// 	int line_height;
// 	int draw_start;
// 	int draw_end;

// 	x = 0;
// 	hit = 0;
// 	while (x < game->win_w)
// 	{
// 		// 1. calcul direction rayon
// 		camera_x = 2 * x / (double)game->win_w - 1;
// 		ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
// 		ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
// 		// 2. dans quelle case de la map on est
// 		map_x = (int)game->player.pos_x;
// 		map_y = (int)game->player.pos_y;
// 		// 3. distance parcourue par le rayon pour aller d'une ligne x a la suivante
// 		delta_dist_x = fabs(1 / ray_dir_x);
// 		delta_dist_y = fabs(1 / ray_dir_y);
// 		// 4. DDA (Digital Differential Analysis) pour trouver le mur
// 		// Calculer step_x, step_y et side_dist_x,	side_dist_y initial
// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1 - game->player.pos_x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1 - game->player.pos_y) * delta_dist_y;
// 		}
// 		// Boucle jusqu'à toucher un mur
// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (game->map.map[map_y][map_x] > 0)
// 				hit = 1;
// 		}
// 		// Calculate distance of perpendicular ray (Euclidean distance would give fisheye effect!)
// 		 if (side == 0)
// 			perp_wall_dist = side_dist_x - delta_dist_x;
// 		 else
// 			perp_wall_dist = side_dist_y - delta_dist_y;
// 		// Calculate height of line to draw on screen
// 		line_height = (int)(game->win_h / perp_wall_dist);
// 		// calculate lowest and highest pixel to fill in current stripe
// 		draw_start = -line_height / 2 + game->win_h / 2;
// 		draw_end = line_height / 2 + game->win_h / 2;
// 		if (draw_start < 0)
//     		draw_start = 0;
// 		if (draw_end >= game->win_h)
//     		draw_end = game->win_h - 1;
// 		//	calcul ou le rayon touche le wall
// 		double wall_x;
// 		if (side == 0)
// 			wall_x = game->player.pos_y + perp_wall_dist * ray_dir_y;
// 		else
// 			wall_x = game->player.pos_x + perp_wall_dist * ray_dir_x;
// 		wall_x -= floor(wall_x); // garder partie decimale
// 		t_img *img;
// 		// convert en coords x de texture
// 		if (side == 0)
// 		{
// 			if (ray_dir_x > 0)
// 				img = game->textures[2];
// 			else
// 				img = game->textures[3];
// 		}
// 		else
// 		{
// 			if (ray_dir_y > 0)
// 				img = game->textures[0];
// 			else
// 				img = game->textures[1];
// 		}
// 		int img_x = (int)(wall_x * (double)img->width);
// 		if (side == 0 && ray_dir_x > 0)
// 			img_x = img->width - img_x - 1;
// 		if (side == 1 && ray_dir_y < 0)
// 			img_x = img->width - img_x - 1;
// 		draw_textured_line(game, x, draw_start, draw_end, img, img_x);
// 		x++;
// 	}
// }

// void	dda(t_game *game, int ray_dir_x, int ray_dir_y, int map_x, int map_y, int delta_dist_x, int delta_dist_y, int step_x, int step_y, int side_dist_x, int side_dist_y)
// {
// 	int	side;
// 	int	hit;

// 	hit = 0;
// 	// 4. DDA (Digital Differential Analysis) pour trouver le mur
// 	// Calculer step_x, step_y et side_dist_x,	side_dist_y initial
// 	if (ray_dir_x < 0)
// 	{
// 		step_x = -1;
// 		side_dist_x = (game->player.pos_x - map_x) * delta_dist_x;
// 	}
// 	else
// 	{
// 		step_x = 1;
// 		side_dist_x = (map_x + 1 - game->player.pos_x) * delta_dist_x;
// 	}
// 	if (ray_dir_y < 0)
// 	{
// 		step_y = -1;
// 		side_dist_y = (game->player.pos_y - map_y) * delta_dist_y;
// 	}
// 	else
// 	{
// 		step_y = 1;
// 		side_dist_y = (map_y + 1 - game->player.pos_y) * delta_dist_y;
// 	}
// 	// Boucle jusqu'à toucher un mur
// 	while (hit == 0)
// 	{
// 		if (side_dist_x < side_dist_y)
// 		{
// 			side_dist_x += delta_dist_x;
// 			map_x += step_x;
// 			side = 0;
// 		}
// 		else
// 		{
// 			side_dist_y += delta_dist_y;
// 			map_y += step_y;
// 			side = 1;
// 		}
// 		if (game->map.map[map_y][map_x] > 0)
// 			hit = 1;
// 	}
// }

