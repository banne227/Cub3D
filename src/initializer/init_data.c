/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 08:18:24 by banne             #+#    #+#             */
/*   Updated: 2026/02/17 18:10:04 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_text init_text(void)
{
	t_text text;

	text.no = NULL;
	text.so = NULL;
	text.we = NULL;
	text.ea = NULL;
	text.f = NULL;
	text.c = NULL;
	return (text);
}

t_data init_data(void)
{
	t_data data;
	int i;

	i = 0;
	while (i < 6)
	{
		data.text_path[i] = NULL;
		i++;
	}
	data.anim.enter_frame = 0;
	data.tex = init_text();
	data.map = init_map();
	data.game = init_game();
	data.start_map_index = -1;
	data.error = false;
	data.screen = (t_img *)malloc(sizeof(t_img));
	if (!data.screen)
		data.error = true;
	if (!data.game.mlx || !data.game.win)
		data.error = true;
	return (data);
}
