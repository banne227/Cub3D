/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: banne <banne@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 08:03:34 by banne             #+#    #+#             */
/*   Updated: 2026/02/24 08:26:51 by banne            ###   ########.fr       */
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

int					rounds(double num);
void				calculate_transform(t_game *game, t_ennemy *e,
						t_sprite_utils *utils);
bool				extension_check(char *filename);
bool				file_check(char *filename);
char				**realloc_map(char **map, int new_size);
char				*trim_endf(char *line);
t_img				create_sprite_img(void *mlx_img);
char				**trim_file(char **file);
char				**get_file(int fd);
int					get_data(char *filename, t_data *data);
bool				have_digit(char *line);
int					get_first_map_index(char **file);
char				*trim_spaces(char *line, int size);
int					max_len(char **file, int start_index, int map_size);
char				**get_map(char **file, t_data *data);
char				*get_direction_texture(char *line);
char				*get_color_texture(char *line);
bool				have_double(char **file);
int					get_value(char **file, t_data *data);
int					parse(int argc, char **argv, t_data *data);
bool				map_valid(t_data *data);
bool				data_valid(t_data *data);
t_data				init_data(void);
t_data				init_data_with_weapons(t_data *data);
bool				init_mlx(t_game *game);
void				copy_without_space(char *dest, const char *src);
void				update_player_data(t_data *data, char d);
bool				is_wall(t_map *map, double x, double y);
int					close_game(void *param);
int					load_textures(t_data *data);
void				free_data(t_data *data);
void				draw_minimap(t_game *game);
void				print_player_pos(t_game *game);
int					render(void *param);
void				move_player(t_game *game);
void				rotate_player(t_data *data);
void				render_menu(t_game *game, t_data *data);
long				timestamp(void);
void				display_enter(t_data *data);
void				play_background_music(t_game *game);
void				destroy_img(void *mlx, void **img);
void				init_anim(t_data *data);
void				load_weapons(t_weapon *weapon, void *mlx);
t_game				init_game(void);
t_map				init_map(void);
int					swap_weapon(t_game *game);
void				draw_weapon(t_game *game);
void				shoot(t_weapon *weapon, t_game *game);
int					bullet_hit(t_weapon *weapon, t_player player, t_map map,
						t_ennemy *ennemies);
void				cut(t_weapon *weapon, t_game *game);
int					hit(t_weapon *weapon, t_player player, t_map map,
						t_ennemy *ennemies);
void				reload(t_weapon *weapon);
void				make_action(t_data *data, int keycode);
void				display_ammo(t_weapon *weapon, t_game *game);
pid_t				play_sounds(char *path);
void				stop_sounds(pid_t pid);
t_ennemy			*init_ennemies(char **map, void *mlx);
void				*load(t_game *game, char *path);
int					take_damage(int damage, double pos_x, double pos_y,
						t_ennemy *ennemies);
void				free_ennemies(t_ennemy *ennemies, void *mlx, int count);
void				open_door(t_map *map, int x, int y);
int					verif_open_door(t_map *map, int x, int y);
bool				is_door(t_map *map, int x, int y);
void				render_pixel(t_game *game, int x, int *y, int color);
void				draw_image_transparent(t_game *game, void *img_src,
						t_dimensions dim, t_pos player_pos);
t_dimensions		get_dim(char *path);
t_dimensions		get_image_dimensions(void *mlx, char *path);
t_weapon			init_weapon(void *mlx);
int					handle_mouse(int button, int x, int y, void *param);
int					handle_mouse_move(int x, int y, void *param);
int					handle_key_press(int keycode, void *param);
int					handle_keys_release(int keycode, void *param);
int					get_texture_color(t_img *img, int x, int y);
int					count_ennemies(char **map);
int					calculate_dimensions(t_sprite_utils *sprite, t_game *game);
int					get_sprite_tex_x(t_sprite_utils *sprite, int x);
void				load_enter(void *mlx, t_anim *enter);
void				init_anim(t_data *data);
bool				is_alive(int pos_x, int pos_y, t_ennemy *ennemies);

// raycasting
void				my_mlx_pixel_put(t_game *game, int x, int y, int color);
void				print_sky_n_floor(t_data *data);
void				load_wall_textures(t_data *data);
void				raycasting(t_game *game);

// raycasting_utils
void				dda(t_raycasting_utils *utils, t_game *game);
void				touch_wall(t_raycasting_utils *utils, t_game *game);
int					convert_coords_textures(t_raycasting_utils *utils,
						t_game *game);
int					pixel_to_fill(t_raycasting_utils *utils, t_game *game);
void				calculate_ray_dir(t_raycasting_utils *utils, t_game *game,
						int x);
void				render_ennemies(t_game *game);

// color utils
int					rgb_to_int(char *rgb_str);

#endif