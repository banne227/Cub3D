/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:30:00 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/19 14:08:56 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	fill_rgd(char **rgb, int *r, int *g, int *b)
{
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
}

int	rgb_to_int(char *rgb_str)
{
	t_rgb	rgb;
	char	**colors;
	int		i;

	i = 0;
	if (!rgb_str)
		return (0);
	colors = ft_split(rgb_str, ',');
	if (!colors || !colors[0] || !colors[1] || !colors[2])
	{
		free_tab(colors);
		return (0);
	}
	fill_rgd(colors, &rgb.r, &rgb.g, &rgb.b);
	while (colors[i])
		free(colors[i++]);
	free(colors);
	return ((rgb.r << 16) | (rgb.g << 8) | rgb.b);
}
