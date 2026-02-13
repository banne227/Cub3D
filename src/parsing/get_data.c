/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 09:15:26 by banne             #+#    #+#             */
/*   Updated: 2026/02/13 16:50:06 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	**realloc_map(char **map, int new_size)
{
	char	**new_map;
	int		i;

	new_map = malloc(sizeof(char *) * (new_size + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (map && i < new_size - 1 && map[i])
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[i] = NULL;
	new_map[i + 1] = NULL;
	if (map)
		free(map);
	return (new_map);
}

char	*trim_endf(char *line)
{
	int		len;
	char	*trimmed;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (len == 0)
		return (line);
	// len -= 1;
	trimmed = malloc(sizeof(char) * (len + 1));
	if (!trimmed)
		return (NULL);
	trimmed = ft_memcpy(trimmed, line, len);
	trimmed[len] = '\0';
	free(line);
	return (trimmed);
}

char	**trim_file(char **file)
{
	int		size;
	char	**trimmed;
	char	*tmp;
	int		i;

	size = 0;
	i = 0;
	trimmed = NULL;
	while (file[i])
	{
		if (ft_strcmp(file[i], "\n") == 0)
		{
			free(file[i]);
			i++;
			continue ;
		}
		trimmed = realloc_map(trimmed, size + 1);
		if (!trimmed)
			return (NULL);
		tmp = trim_endf(file[i]);
		trimmed[size] = tmp;
		size++;
		i++;
	}
	trimmed[size] = NULL;
	free(file);
	return (trimmed);
}

char	**get_file(int fd)
{
	int		size;
	char	**result;
	char	*line;
	char	*tmp;

	size = 0;
	result = NULL;
	line = get_next_line(fd);
	while (line)
	{
		result = realloc_map(result, size + 1);
		if (!result)
			return (NULL);
		tmp = trim_endf(line);
		result[size] = tmp;
		size++;
		line = get_next_line(fd);
	}
	if (!result)
		return (NULL);
	result[size] = NULL;
	return (result);
}

int	get_data(char *filename, t_data *data)
{
	char	**file;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	file = get_file(fd);
	if (!file)
		return (0);
	close(fd);
	if (!get_map(file, data))
		return (0);
	file = trim_file(file);
	if (!file)
		return (0);
	if (!get_value(file, data))
		return (0);
	if (!data_valid(data))
		return (0);
	free_tab(file);
	return (1);
}
