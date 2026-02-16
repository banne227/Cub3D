/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:10:54 by codespace         #+#    #+#             */
/*   Updated: 2026/02/16 08:31:22 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void cut(t_weapon *weapon, t_game *game)
{
    if (weapon->type == 1 || weapon->attack == 0)
        return;
    weapon->frame++;
    if (weapon->frame >= 100)
    {
        weapon->frame = 0;
        weapon->img = weapon->knife.img[0];
        weapon->attack = 0;
    }
    else
        weapon->img = weapon->knife.img[1];
    if (hit(weapon, game->player, game->map))
        weapon->hit = 1;
}

int hit(t_weapon *weapon, t_player player, t_map map)
{
    double hit_x = player.pos_x;
    double hit_y = player.pos_y;
    double step_size = 0.3;
    double distance_traveled = 0.0;

    while (distance_traveled < weapon->knife.range)
    {
        hit_x += player.dir_x * step_size;
        hit_y += player.dir_y * step_size;
        distance_traveled += step_size;

        if ((int)hit_x < 0 || (int)hit_x >= map.width || (int)hit_y < 0 || (int)hit_y >= map.height)
            break;

        if (map.map[(int)hit_y][(int)hit_x] == '1')
            return 0;

        if (map.map[(int)hit_y][(int)hit_x] == 'E')
        {
            // take_damage(weapon->knife.damage, (int)hit_x, (int)hit_y);
            return 1;
        }
    }
    return 0;
}
