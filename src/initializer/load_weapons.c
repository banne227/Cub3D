/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/14 18:48:26 by codespace         #+#    #+#             */
/*   Updated: 2026/02/19 11:57:58 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void *load_weapon_textures(void *mlx, char *path, int w, int h)
{
    void *img;
    t_dimensions dim;

    img = mlx_xpm_file_to_image(mlx, path, &h, &w);
    if (!img)
        ft_printf("Error\nFailed to load weapon texture: %s\n", path);
    dim = get_weapon_dimensions(path);
    return (img);
}

void load_gun_shoot(t_weapon *weapon, void *mlx)
{
    weapon->gun.damage = 20;
    weapon->gun.range = 8;
    weapon->gun.freload = 0;
    weapon->gun.fshoot = 0;
    weapon->gun.ammo = 8;
    weapon->gun.dim = get_weapon_dimensions("textures/weapons/gun/gun.xpm");
    weapon->gun.img = load_weapon_textures(mlx, "textures/weapons/gun/gun.xpm", weapon->gun.dim.width, weapon->gun.dim.height);
    weapon->gun.dim_shoot[0] = get_weapon_dimensions("textures/weapons/gun/gunshot1.xpm");
    weapon->gun.shoot[0] = load_weapon_textures(mlx, "textures/weapons/gun/gunshot1.xpm", weapon->gun.dim_shoot[0].width, weapon->gun.dim_shoot[0].height);
    weapon->gun.dim_shoot[1] = get_weapon_dimensions("textures/weapons/gun/gunshot2.xpm");
    weapon->gun.shoot[1] = load_weapon_textures(mlx, "textures/weapons/gun/gunshot2.xpm", weapon->gun.dim_shoot[1].width, weapon->gun.dim_shoot[1].height);
    weapon->gun.dim_shoot[2] = get_weapon_dimensions("textures/weapons/gun/gunshot3.xpm");
    weapon->gun.shoot[2] = load_weapon_textures(mlx, "textures/weapons/gun/gunshot3.xpm", weapon->gun.dim_shoot[2].width, weapon->gun.dim_shoot[2].height);
    weapon->gun.dim_shoot[3] = get_weapon_dimensions("textures/weapons/gun/gunshot4.xpm");
    weapon->gun.shoot[3] = load_weapon_textures(mlx, "textures/weapons/gun/gunshot4.xpm", weapon->gun.dim_shoot[3].width, weapon->gun.dim_shoot[3].height);
    weapon->gun.dim_shoot[4] = get_weapon_dimensions("textures/weapons/gun/gunshot5.xpm");
    weapon->gun.shoot[4] = load_weapon_textures(mlx, "textures/weapons/gun/gunshot5.xpm", weapon->gun.dim_shoot[4].width, weapon->gun.dim_shoot[4].height);
    weapon->gun.dim_shoot[5] = get_weapon_dimensions("textures/weapons/gun/gunshot6.xpm");
    weapon->gun.shoot[5] = load_weapon_textures(mlx, "textures/weapons/gun/gunshot6.xpm", weapon->gun.dim_shoot[5].width, weapon->gun.dim_shoot[5].height);
}

void load_gun_reload(t_weapon *weapon, void *mlx)
{
    weapon->gun.dim_reload[0] = get_weapon_dimensions("textures/weapons/gun/gunreload1.xpm");
    weapon->gun.reload[0] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload1.xpm", weapon->gun.dim_reload[0].width, weapon->gun.dim_reload[0].height);
    weapon->gun.dim_reload[1] = get_weapon_dimensions("textures/weapons/gun/gunreload2.xpm");
    weapon->gun.reload[1] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload2.xpm", weapon->gun.dim_reload[1].width, weapon->gun.dim_reload[1].height);
    weapon->gun.dim_reload[2] = get_weapon_dimensions("textures/weapons/gun/gunreload3.xpm");
    weapon->gun.reload[2] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload3.xpm", weapon->gun.dim_reload[2].width, weapon->gun.dim_reload[2].height);
    weapon->gun.dim_reload[3] = get_weapon_dimensions("textures/weapons/gun/gunreload4.xpm");
    weapon->gun.reload[3] = load_weapon_textures(mlx, "textures/weapons/gun/gunreload4.xpm", weapon->gun.dim_reload[3].width, weapon->gun.dim_reload[3].height);
}

void load_knife(t_weapon *weapon, void *mlx)
{
    int h1;
    int w1;
    int h2;
    int w2;
    weapon->knife.damage = 10;
    weapon->knife.range = 1;
    weapon->knife.height1 = get_weapon_dimensions("textures/weapons/knife/knife1.xpm").height;
    weapon->knife.width1 = get_weapon_dimensions("textures/weapons/knife/knife1.xpm").width;
    h1 = weapon->knife.height1;
    w1 = weapon->knife.width1;
    weapon->knife.img[0] = load_weapon_textures(mlx, "textures/weapons/knife/knife1.xpm", w1, h1);
    weapon->knife.height2 = get_weapon_dimensions("textures/weapons/knife/knife2.xpm").height;
    weapon->knife.width2 = get_weapon_dimensions("textures/weapons/knife/knife2.xpm").width;
    h2 = weapon->knife.height2;
    w2 = weapon->knife.width2;
    weapon->knife.img[1] = load_weapon_textures(mlx, "textures/weapons/knife/knife2.xpm", w2, h2);
}

void load_weapons(t_weapon *weapon, void *mlx)
{
    load_knife(weapon, mlx);
    load_gun_shoot(weapon, mlx);
    load_gun_reload(weapon, mlx);
    weapon->crosshair[0] = load_weapon_textures(mlx, "textures/weapons/crosshair/crosshair.xpm", 0, 0);
    weapon->crosshair[1] = load_weapon_textures(mlx, "textures/weapons/crosshair/crosshairhit.xpm", 0, 0);
    weapon->ammo[0] = load_weapon_textures(mlx, "textures/weapons/ammo/ammo1.xpm", 0, 0);
    weapon->ammo[1] = load_weapon_textures(mlx, "textures/weapons/ammo/ammo2.xpm", 0, 0);

    if (!weapon->ammo[0])
        ft_printf("Error: Failed to load ammo1.xpm\n");
    if (!weapon->ammo[1])
        ft_printf("Error: Failed to load ammo2.xpm\n");

    if (weapon->knife.img[0])
        weapon->img = weapon->knife.img[0];
    else if (weapon->gun.img)
        weapon->img = weapon->gun.img;
}