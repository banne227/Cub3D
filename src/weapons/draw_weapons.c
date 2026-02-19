/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:50:08 by codespace         #+#    #+#             */
/*   Updated: 2026/02/19 09:33:09 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void draw_weapon(t_game *game)
{
    int x = (game->win_w - 64) / 2;
    int y = game->win_h - 128;

    if (!game->weapon.img)
        return;
    // Utilisez draw_image_transparent avec dimensions fixes pour l'arme
    draw_image_transparent(game, game->weapon.img, 128, 128, x, y);

    x = (game->win_w - 16) / 2;
    y = (game->win_h - 16) / 2;
    if (game->weapon.hit == 0)
    {
        if (game->weapon.crosshair[0])
            draw_image_transparent(game, game->weapon.crosshair[0], 16, 16, x, y);
    }
    else
    {
        if (game->weapon.crosshair[1])
            draw_image_transparent(game, game->weapon.crosshair[1], 16, 16, x, y);
        game->weapon.hit += 1;
        if (game->weapon.hit > 2)
            game->weapon.hit = 0;
    }
    display_ammo(&game->weapon, game);
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