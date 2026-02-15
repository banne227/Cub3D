/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 17:07:54 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/color.h"
#include "../includes/cub3d.h"

static void	print_controls(void)
{
	printf(CYAN "\n");
	printf("░█▀▀░█░█░█▀▄░▀▀█░█▀▄░░░█▀▀░█▀█░█▀█░▀█▀░█▀▄░█▀█░█░░░█▀▀\n");
	printf("░█░░░█░█░█▀▄░░▀▄░█░█░░░█░░░█░█░█░█░░█░░█▀▄░█░█░█░░░▀▀█\n");
	printf("░▀▀▀░▀▀▀░▀▀░░▀▀░░▀▀░░░░▀▀▀░▀▀▀░▀░▀░░▀░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n");
	printf(RESET "\n");
	printf(CYAN "\tW" RESET ": move forward\t");
	printf(CYAN "\tS" RESET ": move backward\n");
	printf(CYAN "\tA" RESET ": move left\t");
	printf(CYAN "\tD" RESET ": move right\n");
	printf(CYAN "\t<" RESET ": rotate left\t");
	printf(CYAN "\t>" RESET ": rotate right\n");
	printf("\n");
}

int	handle_key(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	data->game.last_key = keycode;
	if (keycode == KEY_ESC || data->game.state == STATE_EXIT)
		return (close_game(data));
	if (keycode == KEY_M)
	{
		if (data->game.state == STATE_MENU)
		{
			play_background_music(&data->game);
			data->game.state = STATE_PLAY;
		}
	}
	if (data->game.state == STATE_PLAY)
		make_action(data, keycode);
	move_player(&data->game, keycode);
	rotate_player(data, keycode);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data = init_data();
	if (data.error || parse(argc, argv, &data) != 0)
	{
		free_data(&data);
		return (1);
	}
	printf("Parsing successful!\n");
	print_controls();
	data.game.map = data.map;
	mlx_loop_hook(data.game.mlx, render, &data);
	mlx_hook(data.game.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.game.win, 17, 0, close_game, &data);
	mlx_loop(data.game.mlx);
	stop_background_music(&data.game);
	return (0);
}
