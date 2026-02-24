/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:14:59 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 13:54:17 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	destroy_mlx(t_game *game)
{
	int	i;

	if (game->mlx)
	{
		if (game->win)
			mlx_destroy_window(game->mlx, game->win);
		if (game->img)
			mlx_destroy_image(game->mlx, game->img);
		i = 0;
		while (i < 5)
		{
			if (game->textures[i].img)
			{
				mlx_destroy_image(game->mlx, game->textures[i].img);
				game->textures[i].img = NULL;
			}
			i++;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}

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
	destroy_mlx(game);
	if (data->screen)
		free(data->screen);
}

void	destroy_img(void *mlx, void **img)
{
	if (img && *img)
	{
		mlx_destroy_image(mlx, *img);
		*img = NULL;
	}
}

void	destroy_weapon_images(t_weapon *weapon, void *mlx)
{
	int	i;

	destroy_img(mlx, &weapon->gun.img);
	destroy_img(mlx, &weapon->crosshair[0]);
	destroy_img(mlx, &weapon->crosshair[1]);
	destroy_img(mlx, &weapon->ammo[0]);
	destroy_img(mlx, &weapon->ammo[1]);
	i = 0;
	while (i < 6)
	{
		destroy_img(mlx, &weapon->gun.shoot[i]);
		i++;
	}
	i = 0;
	while (i < 4)
	{
		destroy_img(mlx, &weapon->gun.reload[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		destroy_img(mlx, &weapon->knife.img[i]);
		i++;
	}
}

int	close_game(void *param)
{
	t_data		*data;
	static int	closing = 0;

	if (closing)
		return (0);
	closing = 1;
	printf("Exiting game...\n");
	data = (t_data *)param;
	free(data->game.z_buffer);
	free_ennemies(data->game.ennemys, data->game.mlx,
		count_ennemies(data->map.map));
	if (data && data->game.mlx && data->game.win)
		mlx_clear_window(data->game.mlx, data->game.win);
	if (data && data->game.mlx)
		mlx_loop_end(data->game.mlx);
	if (data && data->game.mlx)
		destroy_weapon_images(&data->game.weapon, data->game.mlx);
	if (data)
		free_data(data);
	exit(0);
	return (0);
}
