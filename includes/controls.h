/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 08:23:32 by banne             #+#    #+#             */
/*   Updated: 2026/02/27 12:35:33 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLS_H
# define CONTROLS_H

# define WIN_W 1280
# define WIN_H 720
# define MOVE_SPEED 0.015
# define ROT_SPEED 0.01
# define SENSI 0.0015

# define MINI_TILE 6
# define WALL_COLOR 0xFFFFFF
# define FLOOR_COLOR 0x777777

# define MAX_AMMO 10

# define RELOAD_SOUND "./sounds/gun_reload.wav"
# define SHOOT_SOUND "./sounds/gun_sound.wav"
# define BACKGROUND_SOUND "./sounds/Mortal_Kombat.wav"
# define KNIFE_SOUND "./sounds/knife_attack.wav"
# define BLOOD_SOUND "./sounds/blood_sound.wav"
# define DEATH_SOUND "./sounds/death_sound.wav"

/* Movement */
# define KEY_W 119 // w
# define KEY_A 97  // a
# define KEY_S 115 // s
# define KEY_D 100 // d
# define KEY_M 109 // m
# define KEY_R 114 // r
# define KEY_E 101 // e

/* mouse click*/
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2

/* Arrows */
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

/* Exit */
# define KEY_ESC 65307
# define KEY_ENTER 65293
# define KEY_SPACE 32

#endif