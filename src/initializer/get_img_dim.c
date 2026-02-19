/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img_dim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:43:01 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 10:32:47 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_dimensions extract_dim(char *line)
{
	t_dimensions dim;
	char **parts;
	char *trimmed;

	if (!line)
		return ((t_dimensions){0, 0});
	ft_printf("DEBUG extract_dim: input line='%s'\n", line);
	trimmed = ft_strtrim(line, "\n");
	trimmed = ft_strtrim(trimmed, "\"");
	trimmed = ft_strtrim(trimmed, "'");
	ft_printf("DEBUG extract_dim: after trim='%s'\n", trimmed);
	parts = ft_split(trimmed, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		ft_printf("DEBUG extract_dim: parts invalid, parts=%p\n", parts);
		if (parts)
			ft_printf("  parts[0]=%p, parts[1]=%p\n", parts[0], parts[1]);
		free_tab(parts);
		free(trimmed);
		return ((t_dimensions){0, 0});
	}
	dim.width = ft_atoi(parts[0]);
	dim.height = ft_atoi(parts[1]);
	ft_printf("DEBUG extract_dim: width=%d, height=%d\n", dim.width, dim.height);
	free_tab(parts);
	free(trimmed);
	return (dim);
}

t_dimensions get_weapon_dimensions(char *path)
{
	t_dimensions dim;
	char *line;
	int fd;
	int i;

	if (!path)
		return ((t_dimensions){0, 0});
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ((t_dimensions){0, 0});
	i = 0;
	dim = (t_dimensions){0, 0};
	line = get_next_line(fd);
	while (i < 3 && line)
	{
		line = get_next_line(fd);
		i++;
	}
	if (line)
	{
		dim = extract_dim(line);
		free(line);
	}
	close(fd);
	return (dim);
}
