/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img_dim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:43:01 by banne             #+#    #+#             */
/*   Updated: 2026/02/23 12:31:57 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_dimensions extract_dim(char *line)
{
	t_dimensions dim;
	char **parts;
	char *trimmed;
	char *temp;

	if (!line)
		return ((t_dimensions){0, 0});
	trimmed = ft_strtrim(line, "\n");
	temp = trimmed;
	trimmed = ft_strtrim(trimmed, "\"");
	free(temp);
	temp = trimmed;
	trimmed = ft_strtrim(trimmed, "'");
	free(temp);
	parts = ft_split(trimmed, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		if (parts)
			ft_printf("  parts[0]=%p, parts[1]=%p\n", parts[0], parts[1]);
		free_tab(parts);
		free(trimmed);
		return ((t_dimensions){0, 0});
	}
	dim.width = ft_atoi(parts[0]);
	dim.height = ft_atoi(parts[1]);
	free_tab(parts);
	free(trimmed);
	return (dim);
}

static void free_n_get_dim(char *line, t_dimensions *dim, int fd)
{
	if (line)
	{
		*dim = extract_dim(line);
	}
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}


t_dimensions get_dim(char *path)
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
	line = NULL;
	while (i++ < 4)
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
			break;
	}
	free_n_get_dim(line, &dim, fd);
	return (dim);
}
