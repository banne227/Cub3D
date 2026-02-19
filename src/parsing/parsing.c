/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:31:00 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:45:31 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	ft_printf("NO: %s\n", data->text_path[NORTH]);
	ft_printf("SO: %s\n", data->text_path[SOUTH]);
	ft_printf("WE: %s\n", data->text_path[WEST]);
	ft_printf("EA: %s\n", data->text_path[EAST]);
	ft_printf("F: %s\n", data->text_path[F]);
	ft_printf("C: %s\n", data->text_path[C]);
	ft_printf("Map (width: %d, height: %d):\n", data->map.width,
		data->map.height);
	while (i < data->map.height)
	{
		ft_printf("%s\n", data->map.map[i]);
		i++;
	}
}

int	parse(int argc, char **argv, t_data *data)
{
	if (argc != 2 || argv[1] == NULL)
	{
		printf("Error\nInvalid number of arguments\n");
		return (1);
	}
	if (!extension_check(argv[1]) || !file_check(argv[1]))
		return (1);
	if (!get_data(argv[1], data))
		return (1);
	printf("Parsed data:\n");
	print_data(data);
	if (!map_valid(data))
		return (1);
	return (0);
}
