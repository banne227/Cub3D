
#include "../../includes/cub3d.h"

void make_action(t_data *data, int keycode)
{
    if (keycode == MOUSE_LEFT)
    {
        if (data->game.weapon.type == 0)
            data->game.weapon.attack = 1;
        else if (data->game.weapon.type == 1
            && data->game.weapon.gun.ammo > 0
            && data->game.weapon.gun.freload == 0)
            data->game.weapon.attack = 1;
    }
    else if (keycode == MOUSE_RIGHT || keycode == 3 || keycode == KEY_R)
    {
        if (data->game.weapon.type == 1
            && data->game.weapon.gun.ammo < 8
            && data->game.weapon.gun.freload == 0)
            data->game.weapon.gun.freload = 1;
    }
    else if (keycode == KEY_M)
    {
        data->game.state = STATE_MENU;
        stop_background_music(&data->game);
    }
    else if (keycode == KEY_SPACE)
        swap_weapon(&data->game);
}