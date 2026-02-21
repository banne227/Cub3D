/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:07:33 by jhauvill         ###   ########.fr       */
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
	data.game.ennemys = init_ennemies(data.game.map.map, data.game.mlx);
	load_wall_textures(&data);
	mlx_loop_hook(data.game.mlx, render, &data);
	mlx_mouse_hide(data.game.mlx, data.game.win);
	mlx_mouse_move(data.game.mlx, data.game.win, WIN_W / 2, WIN_H / 2);
	mlx_hook(data.game.win, 2, 1L << 0, handle_key_press, &data);
	mlx_hook(data.game.win, 3, 1L << 1, handle_keys_release, &data);  
	mlx_hook(data.game.win, 4, 1L << 2, handle_mouse, &data);
	mlx_hook(data.game.win, 6, 1L << 6, handle_mouse_move, &data);
	mlx_hook(data.game.win, 17, 0, close_game, &data);
	mlx_loop(data.game.mlx);
	stop_background_music(&data.game);
	return (0);
}
