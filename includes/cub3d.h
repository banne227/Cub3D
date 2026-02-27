/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:03:34 by banne             #+#    #+#             */
/*   Updated: 2026/02/27 12:51:24 by banne            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../src/libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "color.h"
# include "controls.h"
# include "struct.h"
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

/* ========================================================================== */
/* PARSING */
/* ========================================================================== */
int					parse(int argc, char **argv, t_data *data);
int					get_data(char *filename, t_data *data);
int					get_value(char **file, t_data *data);
char				**get_map(char **file, t_data *data);
bool				data_valid(t_data *data);
bool				map_valid(t_data *data);
bool				file_check(char *filename);
bool				extension_check(char *filename);

/* PARSING UTILITIES */
char				**get_file(int fd);
char				**trim_file(char **file);
char				*trim_endf(char *line);
char				*trim_spaces(char *line, int size);
bool				have_digit(char *line);
bool				have_double(char **file);
int					get_first_map_index(char **file);
int					max_len(char **file, int start_index, int map_size);
char				**realloc_map(char **map, int new_size);
char				*get_direction_texture(char *line);

/* ========================================================================== */
/* INITIALIZATION */
/* ========================================================================== */
t_data				init_data(void);
t_data				init_data_with_weapons(t_data *data);
bool				init_mlx(t_game *game);
t_game				init_game(void);
t_map				init_map(void);
t_weapon			init_weapon(void *mlx);
t_ennemy			*init_ennemies(char **map, void *mlx);
void				init_anim(t_data *data);

/* TEXTURE & RESOURCE LOADING */
int					load_textures(t_data *data);
void				load_weapons(t_weapon *weapon, void *mlx);
void				load_wall_textures(t_data *data);
void				load_enter(void *mlx, t_anim *enter);
void				*load(t_game *game, char *path);

/* ========================================================================== */
/* RAYCASTING */
/* ========================================================================== */
void				raycasting(t_game *game);
void				dda(t_raycasting_utils *utils, t_game *game);
void				touch_wall(t_raycasting_utils *utils, t_game *game);
void				calculate_ray_dir(t_raycasting_utils *utils, t_game *game,
						int x);
int					convert_coords_textures(t_raycasting_utils *utils,
						t_game *game);
int					pixel_to_fill(t_raycasting_utils *utils, t_game *game);
void				print_sky_n_floor(t_data *data);
int					all_accessible(t_map *map, t_game *game);

/* ========================================================================== */
/* RENDERING */
/* ========================================================================== */
int					render(void *param);
void				render_menu(t_game *game, t_data *data);
void				render_ennemies(t_game *game);
void				draw_minimap(t_game *game);
void				draw_weapon(t_game *game);
void				my_mlx_pixel_put(t_game *game, int x, int y, int color);
void				render_pixel(t_game *game, int x, int *y, int color);
void				draw_image_transparent(t_game *game, void *img_src,
						t_dimensions dim, t_pos player_pos);
void				display_enter(t_data *data);
void				display_ammo(t_weapon *weapon, t_game *game);

/* ========================================================================== */
/* PLAYER CONTROLS & INPUT */
/* ========================================================================== */
int					handle_key_press(int keycode, void *param);
int					handle_keys_release(int keycode, void *param);
int					handle_mouse(int button, int x, int y, void *param);
int					handle_mouse_move(int x, int y, void *param);
void				make_action(t_data *data, int keycode);

/* PLAYER MOVEMENT */
void				move_player(t_game *game);
void				rotate_player(t_data *data);
void				update_player_data(t_data *data, char d);
void				print_player_pos(t_game *game);

/* ========================================================================== */
/* WEAPONS & COMBAT */
/* ========================================================================== */
int					swap_weapon(t_game *game);
void				shoot(t_weapon *weapon, t_game *game);
void				cut(t_weapon *weapon, t_game *game);
void				reload(t_weapon *weapon);
int					hit(t_weapon *weapon, t_player player, t_map map,
						t_ennemy *ennemies);
int					bullet_hit(t_weapon *weapon, t_player player, t_map map,
						t_ennemy *ennemies);

/* ========================================================================== */
/* ENEMIES */
/* ========================================================================== */
int					count_ennemies(char **map);
int					take_damage(int damage, double pos_x, double pos_y,
						t_ennemy *ennemies);
void				free_ennemies(t_ennemy *ennemies, void *mlx, int count);
bool				is_alive(int pos_x, int pos_y, t_ennemy *ennemies);
void				calculate_transform(t_game *game, t_ennemy *e,
						t_sprite_utils *utils);
int					calculate_dimensions(t_sprite_utils *sprite, t_game *game);
int					get_sprite_tex_x(t_sprite_utils *sprite, int x);

/* ========================================================================== */
/* MAP & ENVIRONMENT */
/* ========================================================================== */
bool				is_wall(t_map *map, double x, double y);
bool				is_door(t_map *map, int x, int y);
void				open_door(t_map *map, int x, int y);

/* ========================================================================== */
/* AUDIO */
/* ========================================================================== */
pid_t				play_sounds(char *path);
void				stop_sounds(pid_t pid);

/* ========================================================================== */
/* TEXTURE & IMAGE UTILITIES */
/* ========================================================================== */
int					get_texture_color(t_img *img, int x, int y);
t_img				create_sprite_img(void *mlx_img);
t_dimensions		get_image_dimensions(void *mlx, char *path);
t_dimensions		get_dim(char *path);
int					rgb_to_int(char *rgb_str);

/* ========================================================================== */
/* MEMORY & CLEANUP */
/* ========================================================================== */
int					close_game(void *param);
void				free_data(t_data *data);
void				destroy_img(void *mlx, void **img);
void				free_textures(t_game *game);

/* ========================================================================== */
/* UTILITIES */
/* ========================================================================== */
void				copy_without_space(char *dest, const char *src);
long				timestamp(void);
int					rounds(double num);

#endif