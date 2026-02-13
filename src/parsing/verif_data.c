/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 09:43:27 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 16:50:16 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	verif_color_values(char *color)
{
	int	i;
	int	value;

	i = 0;
	if (!color || ft_strlen(color) < 5 || color[0] == ','
		|| color[ft_strlen(color) - 1] == ',')
		return (false);
	while (color[i])
	{
		value = 0;
		while (color[i] == ' ')
			i++;
		while (color[i] && color[i] != ',')
		{
			value = value * 10 + (color[i] - '0');
			i++;
		}
		if (value < 0 || value > 255)
		{
			ft_printf("Error\nColor value %d out of range (0-255)\n", value);
			return (false);
		}
		if (color[i] == ',')
			i++;
	}
	return (true);
}

bool	valid_color(char *color)
{
	int	i;
	int	comma_count;

	i = 0;
	comma_count = 0;
	while (color[i])
	{
		if (color[i] == ',')
			comma_count++;
		else if (!ft_isdigit(color[i]) && color[i] != ' ')
		{
			ft_printf("Error\nColor contains invalid characters\n");
			return (false);
		}
		i++;
	}
	if (comma_count != 2)
	{
		ft_printf("Error\nColor must contain exactly two commas and three numbers\n");
		return (false);
	}
	return (verif_color_values(color));
}

bool	data_valid(t_data *data)
{
	if (!data->text_path[NORTH] || !data->text_path[SOUTH]
		|| !data->text_path[WEST] || !data->text_path[EAST]
		|| !data->text_path[F] || !data->text_path[C])
	{
		ft_printf("Error\nMissing texture or color information\n");
		return (false);
	}
	if (!valid_color(data->text_path[F]) || !valid_color(data->text_path[C]))
		return (false);
	return (true);
}