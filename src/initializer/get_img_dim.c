/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_img_dim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 09:43:01 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 09:58:15 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

t_dimensions extract_dim(char *line)
{
	t_dimensions dim;
	char **parts;

	if (!line)
		return ((t_dimensions){0, 0});
	line = ft_strtrim(line, "\n");
	line = ft_strtrim(line, "'");
	parts = ft_split(line, ' ');
	if (!parts || !parts[0] || !parts[1])
	{
		free_tab(parts);
		return ((t_dimensions){0, 0});
	}
	dim.width = ft_atoi(parts[0]);
	dim.height = ft_atoi(parts[1]);
	free_tab(parts);
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
    line = get_next_line(fd);
    while (i < 2 && line)
    {
        line = get_next_line(fd);
        i++;
    }
    if (line)
    {
		dim = extract_dim(line);
		free(line);
	}
	else
		dim = (t_dimensions){0, 0};
	close(fd);
	return (dim);
}
