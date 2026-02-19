/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:10:09 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 09:29:24 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_pixel_color(char *addr, int line_length, int bits_per_pixel, int x,
		int y)
{
	char	*dst;

	dst = addr + (y * line_length + x * (bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_image_transparent(t_game *game, void *img_src, int img_width,
		int img_height, int pos_x, int pos_y)
{
	char *src_addr;
	int bpp;
	int src_line_len;
	int endian;
	int x;
	int y;
	int screen_x;
	int screen_y;
	unsigned int color;

	src_addr = mlx_get_data_addr(img_src, &bpp, &src_line_len, &endian);

	y = 0;
	while (y < img_height)
	{
		x = 0;
		while (x < img_width)
		{
			screen_x = pos_x + x;
			screen_y = pos_y + y;
			// Vérifier que le pixel est dans les limites de l'écran
			if (screen_x >= 0 && screen_x < game->win_w && screen_y >= 0
				&& screen_y < game->win_h)
			{
				color = get_pixel_color(src_addr, src_line_len, bpp, x, y);
				// Si le pixel n'est pas noir, on le dessine
				if (color != 0x000000 && color != 0xFF000000)
					my_mlx_pixel_put(game, screen_x, screen_y, color);
			}
			x++;
		}
		y++;
	}
}