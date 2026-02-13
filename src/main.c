/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 10:44:13 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/color.h"

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

int handle_key(int keycode, void *param)
{
    t_data *data = (t_data *)param;
    
	printf("Key pressed: %d\n", keycode);
	data->game.last_key = keycode;
    if (keycode == KEY_ESC || data->game.state == STATE_EXIT)
	{
		printf("Exiting game...\n");
		close_game(data);
	}
	if (keycode == KEY_M)
		data->game.state = STATE_MENU;
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
	print_controls();
	data.game.map = data.map;
	//play_background_music(&data.game);
	 mlx_loop_hook(data.game.mlx, render, &data);
	 mlx_hook(data.game.win, 2, 1L<<0, handle_key, &data);
	 mlx_hook(data.game.win, 17, 0, close_game, &data);
	 mlx_loop(data.game.mlx);
	//usleep(5000000); // Keep the program running for a while to hear the music
	//stop_background_music(&data.game);
	return (0);
}
