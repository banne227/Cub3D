/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/02/10 15:47:37 by banne            ###   ########.fr       */
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
    if (keycode == KEY_ESC)
	{
		printf("Exiting game...\n");
		close_game(data);
	}
	if (data->game.state == STATE_MENU)
	{
		if (keycode == KEY_ENTER || keycode == KEY_SPACE)
		{
			if (data->game.menu_option == 0)
			{
				printf("Starting game...\n");
				data->game.state = STATE_PLAY;
			}
			else if (data->game.menu_option == 1)
			{
				printf("Quitting game...\n");
				close_game(data);
			}
		}
		return (0);
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
	print_controls();
	data.game.map = data.map;
	mlx_loop_hook(data.game.mlx, render, &data);
	mlx_hook(data.game.win, 2, 1L<<0, handle_key, &data);
	mlx_hook(data.game.win, 17, 0, close_game, &data);
	mlx_loop(data.game.mlx);
	return (0);
}
