/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:03:34 by banne             #+#    #+#             */
/*   Updated: 2025/12/29 09:53:16 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include "../src/libft/libft.h"

typedef struct s_map
{
    char    **map;
    int     width;
    int     height;
}   t_map;

typedef struct s_data
{
    char    *no;
    char    *so;
    char    *we;
    char    *ea;
    char    *f;
    char    *c;
    t_map   map;
    int     start_map_index;
}   t_data;

bool 	extension_check(char *filename);
bool 	file_check(char *filename);
char 	**realloc_map(char **map, int new_size);
char 	*trim_endf(char *line);
char 	**trim_file(char **file);
char	**get_file(int fd);
int		get_data(char *filename, t_data *data);
bool	have_digit(char *line);
int 	get_first_map_index(char **file);
char 	*trim_spaces(char *line, int size);
int		max_len(char **file, int start_index, int map_size);
char	**get_map(char **file, t_data *data);
char 	*get_direction_texture(char *line);
char 	*get_color_texture(char *line);
bool 	have_double(char **file);
int 	get_value(char **file, t_data *data);
int		parse(int argc, char **argv, t_data *data);
bool    map_valid(t_data *data);
bool    data_valid(t_data *data);

#endif