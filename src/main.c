/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/02/03 08:27:05 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int debug_key(int keycode, void *param)
{
    (void)param;
    printf("Key pressed: %d\n", keycode);
    return (0);
}



int main(int argc, char **argv)
{
	t_data data;

	data = init_data();
	if (data.error || parse(argc, argv, &data) != 0)
		return (1);
	printf("Parsing successful!\n");
	mlx_hook(data.game.win, 2, 1L<<0, debug_key, NULL);
	mlx_loop(data.game.mlx);
	return (0);
}