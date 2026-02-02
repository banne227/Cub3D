/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:31:00 by banne             #+#    #+#             */
/*   Updated: 2026/02/02 16:53:49 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void print_data(t_data *data)
{
	ft_printf("NO: %s\n", data->tex.NO);
	ft_printf("SO: %s\n", data->tex.SO);
	ft_printf("WE: %s\n", data->tex.WE);
	ft_printf("EA: %s\n", data->tex.EA);
	ft_printf("F: %s\n", data->tex.F);
	ft_printf("C: %s\n", data->tex.C);
	ft_printf("Map (width: %d, height: %d):\n", data->map.width, data->map.height);
    for (int i = 0; i < data->map.height; i++)
    {
        ft_printf("%s\n", data->map.map[i]);
    }
}

int parse(int argc, char **argv, t_data *data)
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
