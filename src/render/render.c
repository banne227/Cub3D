/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 10:57:11 by banne             #+#    #+#             */
/*   Updated: 2026/02/20 13:33:21 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	render(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *)param;
	if (data->game.state == STATE_EXIT)
		return (close_game(data));
	if (!data->game.img)
		data->game.img = mlx_new_image(data->game.mlx, data->game.win_w,
				data->game.win_h);
	if (data->game.state == STATE_MENU)
	{
		render_menu(&data->game, data);
		return (0);
	}
	if (data->game.state == STATE_ANIMATION)
	{
		display_enter(data);
		return (0);
	}
	if (data->game.weapon.attack)
	{
		if (data->game.weapon.type == 0)
			cut(&data->game.weapon, &data->game);
		else
			shoot(&data->game.weapon, &data->game);
	}
	if (data->game.weapon.gun.freload > 0)
	{
		reload(&data->game.weapon);
	}
	i = 0;
	while (i < data->game.win_w)
		data->game.z_buffer[i++] = 1e9;
	print_sky_n_floor(data);
	raycasting(&data->game);
	render_ennemies(&data->game);
	draw_minimap(&data->game);
	mlx_put_image_to_window(data->game.mlx, data->game.win, data->game.img, 0,
		0);
	draw_weapon(&data->game);
	move_player(&data->game);
	rotate_player(data);
	return (0);
}
