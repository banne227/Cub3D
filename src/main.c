/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 15:39:30 by banne            ###   ########.fr       */
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

int	handle_mouse(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (data->game.state == STATE_PLAY)
		make_action(data, button);
	return (0);
}

int	handle_mouse_move(int x, int y, void *param)
{
	t_data			*data;
	t_mouse_mouv	mouse;

	data = (t_data *)param;
	mouse.center_x = WIN_W / 2;
	mouse.center_y = WIN_H / 2;
	if (data->game.state != STATE_PLAY)
		return (0);
	if (x == mouse.center_x && y == mouse.center_y)
		return (0);
	mouse.delta_x = x - mouse.center_x;
	mouse.rot_speed = mouse.delta_x * SENSI;
	mouse.olddir_x = data->game.player.dir_x;
	mouse.oldplane_x = data->game.player.plane_x;
	data->game.player.dir_x = data->game.player.dir_x * cos(mouse.rot_speed)
		- data->game.player.dir_y * sin(mouse.rot_speed);
	data->game.player.dir_y = mouse.olddir_x * sin(mouse.rot_speed)
		+ data->game.player.dir_y * cos(mouse.rot_speed);
	data->game.player.plane_x = data->game.player.plane_x * cos(mouse.rot_speed)
		- data->game.player.plane_y * sin(mouse.rot_speed);
	data->game.player.plane_y = mouse.oldplane_x * sin(mouse.rot_speed)
		+ data->game.player.plane_y * cos(mouse.rot_speed);
	mlx_mouse_move(data->game.mlx, data->game.win, mouse.center_x,
		mouse.center_y);
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
	init_data_with_weapons(&data);
	if (data.error)
	{
		free_data(&data);
		return (1);
	}
	printf("Parsing successful!\n");
	print_controls();
	data.game.map = data.map;
	load_textures_raycast(&data);
	mlx_loop_hook(data.game.mlx, render, &data);
	mlx_mouse_hide(data.game.mlx, data.game.win);
	mlx_mouse_move(data.game.mlx, data.game.win, WIN_W / 2, WIN_H / 2);
	mlx_hook(data.game.win, 2, 1L << 0, handle_key, &data);
	mlx_hook(data.game.win, 4, 1L << 2, handle_mouse, &data);
	mlx_hook(data.game.win, 6, 1L << 6, handle_mouse_move, &data);
	mlx_hook(data.game.win, 17, 0, close_game, &data);
	mlx_loop(data.game.mlx);
	stop_background_music(&data.game);
	return (0);
}
