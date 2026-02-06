/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/02/06 12:06:43 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int handle_key(int keycode, void *param)
{
    t_data *data = (t_data *)param;
    
	printf("Key pressed: %d\n", keycode);
    if (keycode == KEY_ESC)
	{
		printf("Exiting game...\n");
		close_game(data);
	}
	move_player(data, keycode);
	rotate_player(data, keycode);
    return (0);
}



int main(int argc, char **argv)
{
	t_data data;

	data = init_data();
	if (data.error || parse(argc, argv, &data) != 0)
	{
		free_data(&data);
		return (1);
	}
	printf("Parsing successful!\n");
	
	data.game.map = data.map;
	mlx_loop_hook(data.game.mlx, render, &data);
	mlx_hook(data.game.win, 2, 1L<<0, handle_key, &data);
	mlx_hook(data.game.win, 17, 0, close_game, &data);
	mlx_loop(data.game.mlx);
	return (0);
}