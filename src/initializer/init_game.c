#include "../../includes/cub3d.h"

t_player init_player(void)
{
	t_player player;

	player.pos_x = 0.0;
	player.pos_y = 0.0;
	player.dir_x = 0.0;
	player.dir_y = 0.0;
	player.plane_x = 0.0;
	player.plane_y = 0.0;
	return (player);
}

t_map init_map(void)
{
	t_map map;

	map.map = NULL;
	map.width = 0;
	map.height = 0;
	return (map);
}

t_weapon init_weapon(void *mlx)
{
	t_weapon weapon;
	int i = 0;

	weapon.attack = 0;
	weapon.frame = 0;
	weapon.hit = 0;
	weapon.type = 0;
	weapon.knife.img[0] = NULL;
	weapon.knife.img[1] = NULL;
	weapon.gun.img = NULL;
	weapon.img = NULL;
	while (i < 6)
		weapon.gun.shoot[i++] = NULL;
	i = 0;
	while (i < 4)
		weapon.gun.reload[i++] = NULL;
	load_weapons(&weapon, mlx);
	weapon.img_height = weapon.knife.height1; ;
	weapon.img_width = weapon.knife.width1;
	weapon.sound = 0;
	return (weapon);
}

t_game init_game(void)
{
	t_game game;

	game.minimap = false;
	game.background_music = false;
	game.mlx = NULL;
	game.win = NULL;
	game.img = NULL;
	game.map = init_map();
	game.win_w = WIN_W;
	game.win_h = WIN_H;
	game.player = init_player();
	game.floor_color = 0;
	game.ceiling_color = 0;
	game.state = STATE_PLAY;
	game.last_key = 0;
	game.menu_option = 0;
	game.music_pid = 0;
	game.ennemys = init_ennemies(game.map.map, game.mlx);
	if (!init_mlx(&game))
		printf("Error\nFailed to initialize game graphics\n");
	else
		game.weapon = init_weapon(game.mlx);
	return (game);
}
