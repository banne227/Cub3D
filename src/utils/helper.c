/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 13:31:48 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 14:55:58 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_anim(t_data *data)
{
	load_enter(data->game.mlx, &data->anim);
	data->anim.last_frame_time = timestamp();
}

int	rounds(double num)
{
	if (num < 0)
		return ((int)(num - 0.5));
	else
		return ((int)(num + 0.5));
}
