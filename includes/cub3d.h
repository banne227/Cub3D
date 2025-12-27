


#ifndef CUB3D_H
#define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
// # include "../libft/libft.h"

struct s_map
{
    char    **map;
    int     width;
    int     height;
}               t_map;


struct s_data
{
    char   *no;
    char   *so;
    char   *we;
    char   *ea;
    char   *f;
    char   *c;
    t_map   map;
    int     start_map_index;
}               t_data;

#endif