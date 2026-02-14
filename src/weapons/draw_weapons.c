#include "../../includes/cub3d.h"

void	draw_weapon(t_game *game)
{
    int x = (game->win_w - 64) / 2;
    int y = game->win_h - 128;

    if (game->weapon.type == 0)
        mlx_put_image_to_window(game->mlx, game->win, game->weapon.knife.img[0], x, y);
    else if (game->weapon.type == 1)
        mlx_put_image_to_window(game->mlx, game->win, game->weapon.gun.img, x, y);
    y = (game->win_h - 64) / 2;
    mlx_put_image_to_window(game->mlx, game->win, game->weapon.crosshair,x, y);
}

int swap_weapon(t_game *game)
{
    if (game->weapon.type == 0)
        game->weapon.type = 1;
    else
        game->weapon.type = 0;
    return (0);
}