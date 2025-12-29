/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:31:00 by banne             #+#    #+#             */
/*   Updated: 2025/12/29 12:44:18 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void print_data(t_data *data)
{
	ft_printf("NO: %s\n", data->no);
	ft_printf("SO: %s\n", data->so);
	ft_printf("WE: %s\n", data->we);
	ft_printf("EA: %s\n", data->ea);
	ft_printf("F: %s\n", data->f);
	ft_printf("C: %s\n", data->c);
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
		return (0);
    return (0);
}
