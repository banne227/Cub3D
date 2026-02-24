/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 08:20:33 by banne             #+#    #+#             */
/*   Updated: 2026/02/24 08:30:48 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				width;
	int				height;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;
typedef struct s_sprite_utils
{
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				line_height;
	int				draw_start_x;
	int				draw_end_x;
	int				draw_start;
	int				draw_end;
	t_img			*img;
}					t_sprite_utils;

typedef struct t_fade
{
	int				x;
	int				y;
	int				bits;
	int				line_len;
	int				endian;
}					t_fade;

typedef struct t_mini
{
	int				x;
	int				y;
	int				bpp;
	int				line_len;
	int				endian;
}					t_mini;

typedef struct s_rgb
{
	int				r;
	int				g;
	int				b;
}					t_rgb;

typedef enum e_game_state
{
	STATE_MENU = 0,
	STATE_PLAY,
	STATE_ANIMATION,
	STATE_EXIT
}					t_game_state;

typedef struct s_text
{
	void			*no;
	void			*so;
	void			*we;
	void			*ea;
	void			*f;
	void			*c;
}					t_text;

typedef struct s_raycasting_utils
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	double			side_dist_x;
	double			side_dist_y;
	int				hit;
	t_img			*img;
	int				side;
	double			perp_wall_dist;
	int				draw_start;
	int				draw_end;
	int				line_height;
}					t_raycasting_utils;

typedef struct s_pos
{
	int				x;
	int				y;
}					t_pos;
typedef struct s_map
{
	char			**map;
	int				width;
	int				height;
}					t_map;

typedef struct s_ennemy
{
	t_pos			pos;
	int				health;
	void			*display;
	void			*img[4];
	bool			alive;
	int				frame;
	int				hit_frame;
	struct s_ennemy	*next;
}					t_ennemy;

typedef struct s_mouse_mouv
{
	int				center_x;
	int				center_y;
	int				delta_x;
	double			rot_speed;
	double			olddir_x;
	double			oldplane_x;
}					t_mouse_mouv;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

typedef struct s_dimentions
{
	int				width;
	int				height;
}					t_dimensions;
typedef struct s_knife
{
	int				damage;
	int				range;
	void			*img[2];
	int				height1;
	int				width1;
	int				height2;
	int				width2;
}					t_knife;

typedef struct s_gun
{
	int				damage;
	int				range;
	void			*img;
	t_dimensions	dim;
	t_dimensions	dim_shoot[6];
	t_dimensions	dim_reload[4];
	int				freload;
	int				fshoot;
	int				ammo;
	void			*shoot[6];
	void			*reload[4];
}					t_gun;
typedef struct s_weapon
{
	int				type;
	void			*img;
	int				width;
	int				height;
	int				attack;
	int				hit;
	int				frame;
	void			*crosshair[2];
	t_knife			knife;
	t_gun			gun;
	void			*ammo[2];
	pid_t			sound;
}					t_weapon;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_img			textures[5];
	t_map			map;
	int				win_w;
	int				win_h;
	t_player		player;
	int				floor_color;
	int				ceiling_color;
	t_game_state	state;
	int				last_key;
	int				menu_option;
	pid_t			music_pid;
	t_weapon		weapon;
	bool			minimap;
	t_ennemy		*ennemys;
	double			*z_buffer;
	bool			keys[65536];
}					t_game;

typedef enum e_direction
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
	F,
	C
}					t_direction;

typedef struct img_utils
{
	char			*src_addr;
	int				bpp;
	int				line_len;
	int				endian;
	unsigned int	color;
	int				x;
	int				y;
}					t_img_utils;
typedef struct s_anim
{
	void			*last_img;
	int				enter_frame;
	long			last_frame_time;
	void			*ent[10];
}					t_anim;

typedef struct s_data
{
	char			*text_path[6];
	t_text			tex;
	t_map			map;
	t_game			game;
	int				start_map_index;
	bool			error;
	int				enter_frame;
	long			last_frame_time;
	t_anim			anim;
	t_img			*screen;
	t_img			*textures[4];
}					t_data;

#endif