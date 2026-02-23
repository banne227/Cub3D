/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_transparent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:10:09 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 14:45:41 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	get_pixel_color(char *addr, int line_length, int bits_per_pixel, t_pos pos)
{
	char	*dst;

	dst = addr + (pos.y * line_length + pos.x * (bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	draw_image_transparent(t_game *game, void *img_src, t_dimensions dim,
	t_pos player_pos)
{
	t_img_utils	img;
	t_pos		pos;

	img.src_addr = mlx_get_data_addr(img_src, &img.bpp,
			&img.line_len, &img.endian);
	pos.y = 0;
	while (pos.y < dim.height)
	{
		pos.x = 0;
		while (pos.x < dim.width)
		{
			img.x = player_pos.x + pos.x;
			img.y = player_pos.y + pos.y;
			if (img.x >= 0 && img.x < game->win_w
				&& img.y >= 0 && img.y < game->win_h)
			{
				img.color = get_pixel_color(img.src_addr, img.line_len, img.bpp,
						pos);
				if (img.color != 0x000000 && img.color != 0xFF000000)
					my_mlx_pixel_put(game, img.x, img.y, img.color);
			}
			pos.x++;
		}
		pos.y++;
	}
}
