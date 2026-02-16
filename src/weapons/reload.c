/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 19:10:58 by codespace         #+#    #+#             */
/*   Updated: 2026/02/16 08:30:00 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void reload(t_weapon *weapon)
{
    if (weapon->type == 0 || weapon->gun.ammo == 8)
        return ;
    weapon->gun.freload++;
    if (weapon->gun.freload % 80 == 0 && weapon->gun.freload / 80 < 4)
        weapon->img = weapon->gun.reload[weapon->gun.freload / 80];
    if (weapon->gun.freload >= 320)
    {
        weapon->img = weapon->gun.img;
        weapon->gun.freload = 0;
        weapon->gun.ammo = 8;
    }
}