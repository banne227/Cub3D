/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_transparency.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 00:00:00 by jhauvill         #+#    #+#             */
/*   Updated: 2026/02/18 00:00:00 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Dessine une image en ignorant le magenta (#FF00FF qui représente la transparence)
** @param game: pointeur vers la structure du jeu
** @param img: l'image à dessiner
** @param x: position x où dessiner
** @param y: position y où dessiner
** @param w: largeur de l'image
** @param h: hauteur de l'image
*/
void	put_image_without_magenta(t_game *game, void *img, int x, int y, int w,
		int h)
{
	char	*img_data;
	char	*win_data;
	int		bpp;
	int		img_line;
	int		win_line;
	int		endian;
	int		i;
	int		j;
	int		color;
	int		px;
	int		py;

	img_data = mlx_get_data_addr(img, &bpp, &img_line, &endian);
	win_data = mlx_get_data_addr(game->img, &bpp, &win_line, &endian);
	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			px = x + i;
			py = y + j;
			// Lire le pixel de l'image source
			color = *(int *)(img_data + (j * img_line + i * (bpp / 8)));
			// Ignorer le magenta (#FF00FF) = transparent
			if ((color & 0x00FFFFFF) != 0x00FF00FF)
			{
				// Vérifier les limites
				if (px >= 0 && px < game->win_w && py >= 0 && py < game->win_h)
				{
					*(int *)(win_data + (py * win_line + px * (bpp
									/ 8))) = color;
				}
			}
			i++;
		}
		j++;
	}
}
