
#include "../../includes/cub3d.h"

int verif_open_door(t_map *map, int x, int y, t_game *game)
{
    if (x < 0 || x >= map->width || y < 0 || y >= map->height)
        return (0);
    if (map->map[y][x] == 'D')
    {
        open_door(game, x, y);
        return (1);
    }
    return (0);
}
