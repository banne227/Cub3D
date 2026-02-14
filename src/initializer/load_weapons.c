/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:48:26 by codespace         #+#    #+#             */
/*   Updated: 2026/02/14 18:49:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	*load_weapon_textures(void *mlx, char *path)
{
    void	*img;
    int		h;
    int		w;

    h = 0;
    w = 0;
    img = mlx_xpm_file_to_image(mlx, path, &h, &w);
    if (!img)
        ft_printf("Error\nFailed to load weapon texture: %s\n", path);
    return (img);
}

void load_weapons(t_weapon *weapon, void *mlx)
{
    weapon->knife.img[0] = load_weapon_textures(mlx, "textures/weapons/knife/knife1.xpm");
    weapon->knife.img[1] = load_weapon_textures(mlx, "textures/weapons/knife/knife2.xpm");
    weapon->gun.img = load_weapon_textures(mlx, "textures/weapons/gun/gun.xpm");
    weapon->gun.shoot[0] = load_weapon_textures(mlx, "textures/weapons/gun/gunshoot1.xpm");
    weapon->gun.shoot[1] = load_weapon_textures(mlx, "textures/weapons/gun/gunshoot2.xpm");
    weapon->gun.shoot[2] = load_weapon_textures(mlx, "textures/weapons/gun/gunshoot3.xpm");
    weapon->gun.shoot[3] = load_weapon_textures(mlx, "textures/weapons/gun/gunshoot4.xpm");
    weapon->gun.shoot[4] = load_weapon_textures(mlx, "textures/weapons/gun/gunshoot5.xpm");
    weapon->gun.shoot[5] = load_weapon_textures(mlx, "textures/weapons/gun/gunshoot6.xpm");
    weapon->gun.reload[0] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload1.xpm");
    weapon->gun.reload[1] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload2.xpm");
    weapon->gun.reload[2] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload3.xpm");
    weapon->gun.reload[3] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload4.xpm");
    weapon->crosshair[0] = load_weapon_textures(mlx, "textures/weapons/crosshair/crosshair.xpm");
    weapon->crosshair[1] = load_weapon_textures(mlx, "textures/weapons/crosshair/crosshairhit.xpm");
}
