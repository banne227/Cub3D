/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 09:15:47 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 17:45:45 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*get_direction_texture(char *line)
{
	char	*no;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	no = malloc(sizeof(char) * (ft_strlen(line) - i + 1));
	if (!no)
		return (NULL);
	ft_strcpy(no, &line[i]);
	no = trim_endf(no);
	return (no);
}

char	*get_color_value(char *line)
{
	char	*color;
	size_t	len;

	len = ft_strlen(line);
	if (len < 2)
		return (NULL);
	color = malloc(sizeof(char) * len);
	if (!color)
		return (NULL);
	copy_without_space(color, &line[1]);
	color = trim_endf(color);
	return (color);
}

bool	have_double(char **file)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = i + 1;
		while (file[j])
		{
			if ((ft_isalpha(file[i][0])) && (ft_strncmp(file[i], file[j],
						2) == 0))
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

int	get_value(char **file, t_data *data)
{
	int	i;

	i = 0;
	if (have_double(file))
	{
		printf("Error\nDuplicate configuration entries found\n");
		return (0);
	}
	while (file[i])
	{
		if (ft_strncmp(file[i], "NO", 2) == 0)
			data->text_path[NORTH] = get_direction_texture(file[i]);
		else if (ft_strncmp(file[i], "SO", 2) == 0)
			data->text_path[SOUTH] = get_direction_texture(file[i]);
		else if (ft_strncmp(file[i], "WE", 2) == 0)
			data->text_path[WEST] = get_direction_texture(file[i]);
		else if (ft_strncmp(file[i], "EA", 2) == 0)
			data->text_path[EAST] = get_direction_texture(file[i]);
		else if (ft_strncmp(file[i], "F", 1) == 0)
			data->text_path[F] = get_color_value(file[i]);
		else if (ft_strncmp(file[i], "C", 1) == 0)
			data->text_path[C] = get_color_value(file[i]);
		i++;
	}
	return (1);
}
