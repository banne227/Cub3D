/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:09:25 by banne             #+#    #+#             */
/*   Updated: 2025/12/29 08:42:32 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_data init_data(void)
{
	t_data data;

	data.no = NULL;
	data.so = NULL;
	data.we = NULL;
	data.ea = NULL;
	data.f = NULL;
	data.c = NULL;
	data.map.map = NULL;
	data.map.width = 0;
	data.map.height = 0;
	data.start_map_index = -1;
	return (data);
}

int main(int argc, char **argv)
{
	t_data data;

	data = init_data();
	if (parse(argc, argv, &data) != 0)
	{
		return (1);
	}
	// Further processing can be done here with the parsed data
	return (0);
}