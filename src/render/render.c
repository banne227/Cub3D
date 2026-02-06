/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:57:11 by banne             #+#    #+#             */
/*   Updated: 2026/02/06 12:06:59 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int render(void *param)
{
	t_data *data = (t_data *)param;

	if (!data->game.img)
		data->game.img = mlx_new_image(data->game.mlx, data->game.win_w, data->game.win_h);
	draw_minimap(&data->game);
	mlx_put_image_to_window(data->game.mlx, data->game.win, data->game.img, 0, 0);
	return (0);
}
