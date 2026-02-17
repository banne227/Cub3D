/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhauvill <jhauvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:30:00 by jhauvill          #+#    #+#             */
/*   Updated: 2026/02/17 18:30:00 by jhauvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int rgb_to_int(char *rgb_str)
{
    int r;
    int g;
    int b;
    char **colors;

    if (!rgb_str)
        return (0);
    colors = ft_split(rgb_str, ',');
    if (!colors || !colors[0] || !colors[1] || !colors[2])
    {
        if (colors)
        {
            int i = 0;
            while (colors[i])
                free(colors[i++]);
            free(colors);
        }
        return (0);
    }
    r = ft_atoi(colors[0]);
    g = ft_atoi(colors[1]);
    b = ft_atoi(colors[2]);
    int i = 0;
    while (colors[i])
        free(colors[i++]);
    free(colors);
    return ((r << 16) | (g << 8) | b);
}
