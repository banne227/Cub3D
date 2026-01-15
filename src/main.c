/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2026/01/15 08:30:05 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
	t_data data;

	data = init_data();
	if (data.error || parse(argc, argv, &data) != 0)
		return (1);
	printf("Parsing successful!\n");
	return (0);
}