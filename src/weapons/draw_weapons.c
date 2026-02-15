/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:50:08 by codespace         #+#    #+#             */
/*   Updated: 2026/02/14 18:52:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_weapon(t_game *game)
{
    int x = (game->win_w - 64) / 2;
    int y = game->win_h - 128;

    if (!game->weapon.img)
        return;
    mlx_put_image_to_window(game->mlx, game->win, game->weapon.img, x, y);
    y = (game->win_h - 64) / 2;
    if (game->weapon.hit == 0)
    {
        if (game->weapon.crosshair[0])
            mlx_put_image_to_window(game->mlx, game->win, game->weapon.crosshair[0], x, y);
    }
    else
    {
        if (game->weapon.crosshair[1])
            mlx_put_image_to_window(game->mlx, game->win, game->weapon.crosshair[1], x, y);
        game->weapon.hit += 1;
        if (game->weapon.hit > 2)
            game->weapon.hit = 0;
    }
}

int swap_weapon(t_game *game)
{
    if (game->weapon.type == 0)
    {
        game->weapon.type = 1;
        game->weapon.img = game->weapon.gun.img;
    }
    else
    {
        game->weapon.type = 0;
        game->weapon.img = game->weapon.knife.img[0];
    }
    game->weapon.attack = 0;
    game->weapon.frame = 0;
    game->weapon.gun.fshoot = 0;
    game->weapon.gun.freload = 0;
    return (0);
}