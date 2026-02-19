/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:30:00 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/19 14:04:36 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fill_rgd(char **rgb, int r, int g, int b)
{
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
}

int	rgb_to_int(char *rgb_str)
{
	int		r;
	int		g;
	int		b;
	char	**colors;
	int		i;

	if (!rgb_str)
		return (0);
	colors = ft_split(rgb_str, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		if (colors)
		{
			i = 0;
			while (colors[i])
				free(colors[i++]);
			free(colors);
		}
		return (0);
	}
	fill_rgd(colors, r, g, b);
	while (colors[i])
		free(colors[i++]);
	free(colors);
	return ((r << 16) | (g << 8) | b);
}
