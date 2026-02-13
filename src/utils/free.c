/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:14:59 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 16:50:36 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_data(t_data *data)
{
	int		i;
	t_game	*game;

	if (!data)
		return ;
	i = 0;
	while (i < 6)
	{
		if (data->text_path[i])
		{
			free(data->text_path[i]);
			data->text_path[i] = NULL;
		}
		i++;
	}
	if (data->map.map)
	{
		free_tab(data->map.map);
		data->map.map = NULL;
	}
	game = &data->game;
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

void	destroy_img(void *mlx, void *img)
{
	if (img)
	{
		mlx_destroy_image(mlx, img);
		img = NULL;
	}
}

int	close_game(void *param)
{
	t_data *data;

	data = (t_data *)param;
	mlx_clear_window(data->game.mlx, data->game.win);
	mlx_loop_end(data->game.mlx);
	stop_background_music(&data->game);
	free_data(data);
	exit(0);
	return (0);
}