/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:03:34 by banne             #+#    #+#             */
/*   Updated: 2026/02/19 12:49:25 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "minilibx-linux/mlx.h"
#include "../src/libft/libft.h"
#include <fcntl.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define WIN_W 1280
#define WIN_H 720
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.03
#define SENSI 0.003

#define MINI_TILE 10
#define WALL_COLOR 0xFFFFFF
#define FLOOR_COLOR 0x777777

#define MAX_AMMO 8

#define RELOAD_SOUND "/home/banne/git_hub/cub/sounds/gun_reload.wav"
#define SHOOT_SOUND "/home/banne/git_hub/cub/sounds/gun_sound.wav"
#define BACKGROUND_SOUND "/home/banne/git_hub/cub/sounds/Mortal_Kombat.wav"
#define KNIFE_SOUND "/home/banne/git_hub/cub/sounds/knife_attack.wav"
#define BLOOD_SOUND "/home/banne/git_hub/cub/sounds/blood_sound.wav"
#define DEATH_SOUND "/home/banne/git_hub/cub/sounds/death_sound.wav"

/* Movement */
#define KEY_W 119 // w
#define KEY_A 97  // a
#define KEY_S 115 // s
#define KEY_D 100 // d
#define KEY_M 109 // m
#define KEY_R 114 // r
#define KEY_E 101 // e

/* mouse click*/
#define MOUSE_LEFT 1
#define MOUSE_RIGHT 2

/* Arrows */
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_UP 65362
#define KEY_DOWN 65364

/* Exit */
#define KEY_ESC 65307
#define KEY_ENTER 65293
#define KEY_SPACE 32

typedef enum e_game_state
{
	STATE_MENU = 0,
	STATE_PLAY,
	STATE_ANIMATION,
	STATE_EXIT
} t_game_state;

typedef struct s_text
{
	void *no;
	void *so;
	void *we;
	void *ea;
	void *f;
	void *c;
} t_text;

typedef struct s_pos
{
	int x;
	int y;
} t_pos;
typedef struct s_map
{
	char **map;
	int width;
	int height;
} t_map;

typedef struct s_ennemy
{
	t_pos pos;
	int health;
	void *display;
	void *img[4];
	bool alive;
	int frame;
	struct s_ennemy *next;
} t_ennemy;

typedef struct s_mouse_mouv
{
	int center_x;
	int center_y;
	int delta_x;
	double rot_speed;
	double olddir_x;
	double oldplane_x;
} t_mouse_mouv;

typedef struct s_player
{
	double pos_x;
	double pos_y;
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
} t_player;

typedef struct s_dimentions
{
	int width;
	int height;
} t_dimensions;
typedef struct s_knife
{
	int damage;
	int range;
	void *img[2];
	int height1;
	int width1;
	int height2;
	int width2;
} t_knife;

typedef struct s_gun
{
	int damage;
	int range;
	void *img;
	t_dimensions dim;
	t_dimensions dim_shoot[6];
	t_dimensions dim_reload[4];
	int freload;
	int fshoot;
	int ammo;
	void *shoot[6];
	void *reload[4];
} t_gun;
typedef struct s_weapon
{
	int type;
	void *img;
	int width;
	int height;
	int attack;
	int hit;
	int frame;
	void *crosshair[2];
	t_knife knife;
	t_gun gun;
	void *ammo[2];
	pid_t sound;
} t_weapon;

typedef struct s_img
{
	void *img;
	char *addr;
	int width;
	int height;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_game
{
	void *mlx;
	void *win;
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length; // cree nouvelle struct pour le screen
	int endian;		 // pas oublier de init tt se que tu met dans la structure
	t_img textures[4];
	t_map map;
	int win_w;
	int win_h;
	t_player player;
	int floor_color;
	int ceiling_color;
	t_game_state state;
	int last_key;
	int menu_option;
	pid_t music_pid;
	t_weapon weapon;
	bool minimap;
	bool key_w;
	bool key_a;
	bool key_s;
	bool key_d;
	bool key_left;
	bool key_right;
	t_ennemy *ennemys;
	bool background_music;
} t_game;

typedef enum e_direction
{
	NORTH = 0,
	SOUTH,
	WEST,
	EAST,
	F,
	C
} t_direction;

typedef struct s_anim
{
	void *last_img;
	int enter_frame;
	long last_frame_time;
	void *ent[10];
} t_anim;

typedef struct s_data
{
	char *text_path[6];
	t_text tex;
	t_map map;
	t_game game;
	int start_map_index;
	bool error;
	int enter_frame;
	long last_frame_time;
	t_anim anim;
	t_img *screen;
	t_img *textures[4];
} t_data;

bool extension_check(char *filename);
bool file_check(char *filename);
char **realloc_map(char **map, int new_size);
char *trim_endf(char *line);
char **trim_file(char **file);
char **get_file(int fd);
int get_data(char *filename, t_data *data);
bool have_digit(char *line);
int get_first_map_index(char **file);
char *trim_spaces(char *line, int size);
int max_len(char **file, int start_index, int map_size);
char **get_map(char **file, t_data *data);
char *get_direction_texture(char *line);
char *get_color_texture(char *line);
bool have_double(char **file);
int get_value(char **file, t_data *data);
int parse(int argc, char **argv, t_data *data);
bool map_valid(t_data *data);
bool data_valid(t_data *data);
t_data init_data(void);
t_data init_data_with_weapons(t_data *data);
bool init_mlx(t_game *game);
void copy_without_space(char *dest, const char *src);
void update_player_data(t_data *data, char d);
bool is_wall(t_map *map, double x, double y);
int close_game(void *param);
int load_textures(t_data *data);
void free_data(t_data *data);
void draw_minimap(t_game *game);
void print_player_pos(t_game *game, int *img_data, int line_len, int x, int y);
int render(void *param);
void move_player(t_game *game, int keycode);
void rotate_player(t_data *data, int keycode);
void render_menu(t_game *game, t_data *data);
long timestamp(void);
void display_enter(t_data *data);
void play_background_music(t_game *game);
void stop_background_music(t_game *game);
void destroy_img(void *mlx, void *img);
void init_anim(t_data *data);
void load_weapons(t_weapon *weapon, void *mlx);
t_game init_game(void);
t_map init_map(void);
int swap_weapon(t_game *game);
void draw_weapon(t_game *game);
void shoot(t_weapon *weapon, t_game *game);
int bullet_hit(t_weapon *weapon, t_player player, t_map map, t_ennemy *ennemies);
void cut(t_weapon *weapon, t_game *game);
int hit(t_weapon *weapon, t_player player, t_map map, t_ennemy *ennemies);
void reload(t_weapon *weapon);
void make_action(t_data *data, int keycode);
void display_ammo(t_weapon *weapon, t_game *game);
pid_t play_sounds(char *path);
void stop_sounds(pid_t pid);
t_ennemy *init_ennemies(char **map, void *mlx);
void *load(t_game *game, char *path);
void take_damage(int damage, int pos_x, int pos_y, t_ennemy *ennemies);
void open_door(t_map *map, int x, int y);
int verif_open_door(t_map *map, int x, int y);
bool is_door(t_map *map, int x, int y);
void draw_image_transparent(t_game *game, void *img_src, int img_width, int img_height, int pos_x, int pos_y);
t_dimensions get_weapon_dimensions(char *path);
t_dimensions get_image_dimensions(void *mlx, char *path);

// raycasting
void my_mlx_pixel_put(t_game *game, int x, int y, int color);
void print_sky_n_floor(t_data *data);
void load_textures_raycast(t_data *data);
void raycasting(t_game *game);

// color utils
int rgb_to_int(char *rgb_str);

#endif